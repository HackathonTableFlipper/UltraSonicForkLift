package sonic.ultra.forklift

import android.app.Activity
import android.nfc.Tag
import android.os.Bundle
import android.text.Editable
import android.util.Log
import android.widget.EditText
import com.beust.klaxon.*

import khttp.responses.Response
import kotlinx.android.synthetic.main.activity_main.*
import sonic.ultra.forklift.messages.*

import khttp.delete as httpDelete

//import sonic.ultra.forklift.messages.Foo

class MainActivity : Activity() {

    companion object {
        val TAG = "[My_" + MainActivity::class.java.simpleName + "_TAG]"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        val json = Klaxon().toJsonString(ListLocationsRequest())

        khttp.async.post("http://www.google.com", allowRedirects = true, data = json,onError = {
            Log.d(TAG, "Error message: $message")
        }) {
            Log.d(TAG, "Status Code: $statusCode")
            Log.d(TAG, "Response Text: $text")
        }


    }
}
