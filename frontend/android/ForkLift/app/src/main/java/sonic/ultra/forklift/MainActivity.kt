package sonic.ultra.forklift

import android.app.Activity
import android.os.Bundle
import android.text.Editable
import android.util.Log
import android.widget.EditText

import com.beust.klaxon.Klaxon
import com.beust.klaxon.json
import kotlinx.android.synthetic.main.activity_main.*
import sonic.ultra.forklift.messages.Device


//import sonic.ultra.forklift.messages.Foo

class MainActivity : Activity() {

    companion object {
        val TAG = "[My " + MainActivity::class.java.simpleName + " TAG]"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val foo = Device("MAC Adress", "Fork 1", "Kraftwerk")
        val jsonString = Klaxon().toJsonString(foo)
        Log.d(TAG, jsonString)
    }
}
