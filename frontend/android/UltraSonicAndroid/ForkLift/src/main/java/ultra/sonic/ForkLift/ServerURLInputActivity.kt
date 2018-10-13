package ultra.sonic.ForkLift

import android.content.Intent
import android.os.Bundle
import android.support.design.widget.Snackbar
import android.support.v7.app.AppCompatActivity
import android.support.v7.widget.RecyclerView
import android.util.Log
import android.view.View
import kotlinx.android.synthetic.main.activity_item_list.*
import kotlinx.android.synthetic.main.item_list.*
import ultra.sonic.ForkLift.content.OverviewContent

class ServerURLInputActivity: AppCompatActivity() {

    /**
     * Whether or not the activity is in two-pane mode, i.e. running on a tablet
     * device.
     */
    private var twoPane: Boolean = false

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.d(LOG_TAG, "onCreate was called")

        setContentView(R.layout.ip_input)

//        setSupportActionBar(toolbar)
//        toolbar.title = title

//        fab.setOnClickListener { view ->
//            Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
//                    .setAction("Action", { view ->
//                        val intent = Intent(view.context, ItemListActivity::class.java)
//                        view.context.startActivity(intent)
//                    }).show()
//        }

//        if (item_detail_container != null) {
//            // The detail container view will be present only in the
//            // large-screen layouts (res/values-w900dp).
//            // If this view is present, then the
//            // activity should be in two-pane mode.
//            twoPane = true
//        }

    }

    companion object {
        const val ARG_SERVER_ID = "server_id"
        val LOG_TAG = ServerURLInputActivity.javaClass.simpleName
        val URL = ""
    }
}