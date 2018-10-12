# Frontend API


API-URL: <%server>/frontendAPI/

## ListLocations
request:
```
{
    "type": "ListLocations"
}
```
response:
```
{
    "type": "ListLocations",
    "data": [<string(32)>]
}
```

## ListDevices(InTimeSpan)
request:
```
{
    "type": "ListDevices",
    "start": <DateTime>|null,
    "end":   <DateTime>|null,
    "location": <string(32)>|null
}
```
response:
```
{
    "type": "ListDevices",
    "data": [
        {
        	"id": <string(12)>,
        	"name": <string(32)>, 
        	"location": <string(32)>
        },
        ...
    ]
}
```

## OverviewForDevices(InTimeSpan)
request:
```
{
	"type": "ListOverview",
    "devices": [<id>, ...],
    "start": <DateTime>,
    "end": <DateTime>
}
```
response:
```
{
    "type": "ListOverview",
    "data": [
         {
            "id": <string(12)>, 
            "name": <string(32)>,
            "location": <string(32)>, 
            "loadedTime": <sum([duration(<DateTime>, <DateTime>)])>,
            "emptyTime":  <sum([duration(<DateTime>, <DateTime>)])>
        },
        ...
    ]
}
```

## DataForDevices(InTimeSpan)
request:
```
{
	"type": "ListData",
    "devices": [<id>, ...],
    "start": <DateTime>,
    "end": <DateTime>
}
```
response:
```
{
    "type": "ListData",
	"data": [
        {
            "id":<string(12)>, 
            "name":<string(32)>,
            "location":<string(32)>, 
            "loadedTimes": [(<DateTime>, <DateTime>)],
            "emptyTimes":  [(<DateTime>, <DateTime>)]
        },
        ...
    ]
}
```