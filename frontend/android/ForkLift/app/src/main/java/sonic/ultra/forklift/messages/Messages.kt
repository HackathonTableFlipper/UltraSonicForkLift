package sonic.ultra.forklift.messages

data class ListConnectionsRequest(
        val type : String = "ListConnections"
)

data class ListConnectionsRepsonse(
        val type : String = "ListConnections",
        val locations: List<Location>
)

data class ListDevicesRequest(
        val type : String = "ListDevices",
        val start : String?,
        val end : String?,
        val location : Location?
)

data class ListDevicesResponse(
        val type : String = "ListDevices",
        val data : List<Device>
)

data class OverviewForDevicesRequest(
        val type: String = "ListOverview",
        val devices : List<Id>,
        val start : DateTimeString,
        val end : DateTimeString
)

data class OverviewForDevicesRepsonse(
        val type: String = "ListOverview",
        val data : List<OverviewEntry>
)

data class DataForDevicesRequest(
        val type: String = "ListData",
        val devices : List<Id>,
        val start : DateTimeString,
        val end : DateTimeString
)

data class DataForDevicesRepsonse(
        val type : String = "ListData",
        val data : List<DataEntry>
)



// AST

typealias Location = String
typealias Id = String
typealias DateTimeString = String?

data class Device(
        val id : Id,
        val name : String,
        val location : Location
)

data class OverviewEntry(
        val id : String,
        val name : String,
        val location : Location,
        val loadedTime : Long,
        val emptyTime : Long
)

data class DataEntry(
        val id : Id,
        val name : String,
        val location : Location,
        val loadedTimes : List<List<DateTimeString>>,
        val emptyTimes : List<List<DateTimeString>>
)



