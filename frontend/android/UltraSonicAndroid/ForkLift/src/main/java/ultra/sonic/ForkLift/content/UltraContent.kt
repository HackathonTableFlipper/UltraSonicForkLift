package ultra.sonic.ForkLift.content

import java.time.Duration
import java.util.ArrayList
import java.util.HashMap
import java.util.Date

object UltraContent {

    /**
     * An array of sample (dummy) items.
     */
    val ITEMS: MutableList<OverviewItem> = ArrayList()

    /**
     * A map of sample (dummy) items, by ID.
     */
    val ITEM_MAP: MutableMap<String, OverviewItem> = HashMap()

    private val COUNT = 25

    init {
        // Add some sample items.
        for (i in 1..COUNT) {
            addItem(createOverviewItem(i))
        }
    }

    private fun addItem(item: OverviewItem) {
        ITEMS.add(item)
        ITEM_MAP[item.name] = item
    }

    private fun createOverviewItem(position: Int): OverviewItem {
        return OverviewItem("Fork Lift $position",
                "Location $position",
                Duration.ofHours(position * 100L ),
                Duration.ofHours(80L * position),
                Duration.ofHours(20L * position),
                80)
    }


    /**
     * A dummy item representing a piece of content.
     */
    data class OverviewItem(val name: String
                            , val location: String
                            , val all: Duration
                            , val loaded: Duration
                            , val unloaded: Duration
                            , val percent: Int) {
        override fun toString(): String =
                "Fork Lift Name:             $name\n" +
                "Location:                   $location\n" +
                "Total time of usage:        $all\n" +
                "Time under load:            $loaded\n" +
                "Time without load:          $unloaded\n" +
                "Percent of loaded activity: $percent"
    }
}
