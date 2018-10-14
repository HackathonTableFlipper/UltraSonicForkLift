{-# LANGUAGE DeriveGeneric, OverloadedStrings #-}

module Lib
    ( someFunc
    ) where

import GHC.Generics
import Messages
import Network.HTTP
import Network.Stream
import Network.HTTP.Headers
import Network.HTTP.Base
import Network.Mail.SMTP 
import Network.Mail.Mime hiding (simpleMail)
import Network.URI
import Control.Concurrent.MVar
import Control.Concurrent
import System.Environment
import Data.ByteString.Lazy hiding (filter,map, head, null, tail, putStrLn)
import qualified Data.ByteString.Char8 as C
import Data.ByteString.Search
import Data.Aeson
import Data.Text.Encoding
import qualified Data.Text.Internal as T


type MailContact = (String,T.Text)

someFunc :: IO ()
someFunc = do
    mmaillist <- newEmptyMVar :: IO (MVar [MailContact])
    putMVar mmaillist [("imap.uni-bremen.de", "ganser.@uni-bremen.de")]
    mailLoopStart mmaillist
--    mailinProcess <- forkIO $ mailLoopStart mmaillist
--    return ()


mailLoopStart mmaillist = do
    args <- getArgs
    case args of
        [] -> return ()
        xs -> mailloop mmaillist $ "http://"++ (head args) ++ (head $ tail args) 


mailloop mmaillist url = do
    putStrLn $ "DEBUG | " ++ show url
    triggerNotification <- hanalytics url
    if (not triggerNotification) then do
        threadDelay 10000000
        mailloop mmaillist url
    else do 
        sendmails mmaillist
        threadDelay 10000000
        mailloop mmaillist url

sendmails mmaillist = do
    list <- readMVar mmaillist
    let hnmails = map createMail list
    mapM (\hm -> putStrLn $ "DEBUG | " ++ show hm) hnmails
    mapM (\(hostName, mail) -> sendMail hostName mail) hnmails


createMail (hostname, adressString) = 
    (hostname, simpleMail 
        (Address (Just "Hanalytics") "hanalytics@haskell.lambda")
        [Address (Just "Expert") (adressString)] 
        []
        []  
        "Hanalytics Mail"      
        [plainTextPart "Some Fork Lifters are used less than 10 percent their time with load, check out the webpage for further information"])


hanalytics url = do 
    deviceResp <- simpleHTTP $ createDeviceRequest url
    putStrLn $ "DEBUG | " ++ show deviceResp
    devIds <- getDeviceIds' deviceResp
    overResp <- simpleHTTP $ createOverRequest url devIds
    putStrLn $ "DEBUG | " ++ show overResp
    result <- hanalyse' overResp
    putStrLn $ "DEBUG | " ++ "Resutls of the calculation: trigger=" ++ show result
    return result

headers = [
        Header HdrAccept "text/*"
    ]

contentType = "Conent-Type:text/json"

replaceNull :: C.ByteString -> ByteString
replaceNull = replace escapedNull notEscapedNull
    where 
        escapedNull :: C.ByteString
        escapedNull = "\"null\""
        notEscapedNull :: C.ByteString
        notEscapedNull = "null"

ldqJson :: String
ldqJson = C.unpack $ toStrict $ replaceNull $ toStrict $ encode $ LDQ "ListDevices" "2000-1-1 12:00" "2020-1-1 12:00" "null"

oqJson :: [String] -> String
oqJson deviceIds = C.unpack $ toStrict $ encode $ OQ "ListOverview" deviceIds "2000-1-1 12:00" "2020-1-1 12:00"

createDeviceRequest url = postRequestWithBody url contentType $ ldqJson
createOverRequest url deviceIds = postRequestWithBody url contentType $ oqJson deviceIds


getDeviceIds' (Left connError) = return []
getDeviceIds' (Right response) = getDeviceIds response

getDeviceIds (Response _ _ _ stringbody) = do
    putStrLn $ "DEBUG | " ++ "body of the response: " ++ show stringbody
    let byteBody = fromStrict $ C.pack stringbody
    let devices = decode byteBody :: Maybe LDResponse
    putStrLn $ "DEBUG | " ++ "Decoded deviceList message: " ++ show devices
    case devices of
        Nothing -> return []
        Just (LDA _ ds) -> return $ map (\(D id _ _) -> id) $ ds



hanalyse' (Left connError) = return False
hanalyse' (Right response) = hanalyse response
-- Hanalytics
--hanalyse :: Response ByteString -> IO Bool
hanalyse (Response _ _ _ stringbody) = do
      putStrLn $ "DEBUG | " ++ "body of the response: " ++ show stringbody
      let byteBody = fromStrict $ C.pack stringbody
      let overview = decode byteBody :: Maybe OResponse
      putStrLn $ "DEBUG | " ++ "Decoded Overview message: " ++ show overview
      case overview of
        Nothing -> return False
        Just (OA _ oes) -> do
            mapM (\oe -> putStrLn $ "DEBUG | " ++ show oe) oes
            let percents = map (\oe -> (loadedTime oe + emptyTime oe) `div` loadedTime oe) oes
            let trigger = not $ null $ filter (<10) percents --Hardcoded 10 percent mark
            return trigger


    
     

