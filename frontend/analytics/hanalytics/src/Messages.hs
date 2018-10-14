{-# LANGUAGE DeriveGeneric, OverloadedStrings #-}

module Messages where


import GHC.Generics
import Data.Aeson
import Data.ByteString.Lazy

data DataEntry = DE String String String [[String]] [[String]] deriving (Generic, Show)

instance FromJSON DataEntry where
    parseJSON (Object v) = DE
        <$> v .: "id"
        <*> v .: "name"
        <*> v .: "location"
        <*> v .: "loadedTimes"
        <*> v .: "emptyTimes"
    parseJSON _ = undefined

data Device = D String String String deriving (Generic,Show)

instance FromJSON Device where
    parseJSON (Object v) = D
        <$> v .: "id"
        <*> v .: "name"
        <*> v .: "location"
    parseJSON _ = undefined

data OverviewEntry = 
    OE { id :: String
       , name :: String
       , location :: String
       , loadedTime :: Integer
       , emptyTime :: Integer
    } deriving (Generic, Show)

instance FromJSON OverviewEntry



data LLRequest = LLQ String deriving (Generic,Show)

data LLResponse = LLA String [String] deriving (Generic,Show)

instance ToJSON LLRequest where
    toEncoding (LLQ t) = pairs ("type" .= t)

instance FromJSON LLResponse where
    parseJSON (Object v) = do
        t  <- v .: "type"
        ls <- v .: "data"
        return (LLA t ls)
    parseJSON _ = undefined



data ORequest = OQ String [String] String String deriving (Generic,Show)

data OResponse = OA String [OverviewEntry] deriving (Generic,Show)

instance ToJSON ORequest where
    toEncoding (OQ t ds start end) = 
        pairs ("type" .= t <> "devices" .= ds <> "start" .= start <> "end" .= end)
instance FromJSON OResponse where
    parseJSON = withObject "OResponse" $ \v -> OA
        <$> v .: "type"
        <*> v .: "data"



data LDRequest = LDQ String String String String deriving (Generic,Show)

data LDResponse = LDA String [Device] deriving (Generic,Show)

instance ToJSON LDRequest where
    toEncoding (LDQ t start end l) = 
        pairs ("type" .= t <> "start" .= start <> "end" .= end <> "location" .= l)
instance FromJSON LDResponse where
    parseJSON = withObject "LDResponse" $ \v -> LDA
        <$> v .: "type"
        <*> v .: "data"


data DataRequest = DataQ String [String] String String deriving (Generic,Show)

data DataResponse = DataA String [DataEntry] deriving (Generic,Show)

instance ToJSON DataRequest where
    toEncoding (DataQ t ids start end) = 
        pairs ("type" .= t <> "devices" .= ids <> "start" .= start <> "end" .= end)
instance FromJSON DataResponse where
    parseJSON = withObject "DataEntry" $ \v -> DataA
        <$> v .: "type"
        <*> v .: "data"