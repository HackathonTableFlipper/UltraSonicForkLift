# Microcontroller API

API-URL: <%server>/frontendAPI/

## Init Handshake

microcontroller:
request:
```
{
    "type": "init",
    "mac": <MAC-adress 48Bit>,
    "name": <%name>,
    "location": <%location>
}
```
response:
Status 200, resend on error (try 5 times -> inti mode (display error [name | location | mac-address]) )

## Log request
request:
```
{   
    "mac": <MAC-adress 48Bit>,
    "type": "log",
    "data": [
        {"load": <bool>, "start":<DateTime>, "end":<DateTime>}
        ,...
    ]
}
```

response:
Status 200, resend on error (try 5 times)

## Try connection
Ping