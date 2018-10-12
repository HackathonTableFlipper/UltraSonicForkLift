# Microcontroller API

## Init Handshake
microcontroller:
{
    "type": "init",
    "mac": <MAC-adress 48Bit>,
    "name": <%name>,
    "location": <%location>
}

answer:
Status 200, resend on error (try 5 times -> inti mode (display error [name | location | mac-address]) )

## Log request
{   
    "mac": <MAC-adress 48Bit>,
    "type": "log",
    "data": [
        {"load": <bool>, "start":<DateTime>, "end":<DateTime>}
        ,...
    ]
}

answer:
Status 200, resend on error (try 5 times)

## Try connection
Ping