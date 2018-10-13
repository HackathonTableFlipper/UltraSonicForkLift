package sonic.ultra.forklift.messages

import com.beust.klaxon.*
import com.beust.klaxon.EnumConverter
import org.json.JSONArray

data class ListLocationsRequest(
        val type : String = "ListLocations"
)

data class ListLocationsRepsonse(
        val type : String = "ListLocations",
        val data: List<Location>
)

class StringConverter : Converter {
    override fun toJson(value: Any): String = value.toString()
    override fun fromJson(jv: JsonValue) = jv.inside.toString()
    override fun canConvert(cls: Class<*>) : Boolean = cls == String.javaClass
}

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
data class StringObject(
        val value : String
)
typealias Location = String
typealias Id = String
typealias DateTimeString = String?
//data class Location(
//        val value: String
//)
//data class Id(
//        val value : String
//)
//data class DateTimeString(
//        val value: String?
//)

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



