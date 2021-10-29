package uz.gita.circleimage

import android.app.Activity
import android.content.Intent
import android.graphics.Bitmap
import android.graphics.ImageDecoder
import android.net.Uri
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.provider.MediaStore
import android.util.Log
import androidx.activity.result.contract.ActivityResultContracts
import by.kirich1409.viewbindingdelegate.viewBinding
import uz.gita.circleimage.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

    private val binding by viewBinding(ActivityMainBinding::bind)

    companion object {
        init {
            System.loadLibrary("main-activity")
        }
    }

//
//    var resultLauncher =
//        registerForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
//            if (result.resultCode == Activity.RESULT_OK) {
//                val data: Intent? = result.data
//                val selectedImage: Uri? = data?.data
//                try {
//                    selectedImage?.let {
//                        if (Build.VERSION.SDK_INT < 28) {
//                            val bitmap =
//                                MediaStore.Images.Media.getBitmap(contentResolver, selectedImage)
//                            binding.image1.setImageBitmap(bitmap)
//                        } else {
//
//                            val source = ImageDecoder.createSource(contentResolver, selectedImage)
//                            val bitmap = ImageDecoder.decodeBitmap(source)
//
//                            val stream = ByteArrayOutputStream()
//                            bitmap.compress(Bitmap.CompressFormat.PNG, 100, stream)
//                            val imageBytes = stream.toByteArray()
//                            Log.d("TTT", "size: ${imageBytes.size} byte array: ${imageBytes.contentToString()}")
//                            val newBytes = makeCircle(imageBytes)
//
//                            val bitmap2 = BitmapFactory.decodeByteArray(newBytes, 0, newBytes.size)
//                            binding.image1.setImageBitmap(bitmap2)
//                        }
//                    }
//                } catch (e: Exception) {
//                    e.printStackTrace()
//                }
//
//            }
//        }
//


   private var resultLauncher = registerForActivityResult(ActivityResultContracts.StartActivityForResult()) { result ->
            if (result.resultCode == Activity.RESULT_OK) {
                Log.d("TTT", "Launcher: Ok")
                val data: Intent? = result.data
                val selectedImage: Uri? = data?.data
                try {
                    selectedImage?.let {
                        if (Build.VERSION.SDK_INT < 28) {
                            val bitmap = MediaStore.Images.Media.getBitmap(contentResolver, selectedImage)
                            binding.image1.setImageBitmap(bitmap)
                        } else {
                            val source = ImageDecoder.createSource(contentResolver, selectedImage)
                            val bitmap = ImageDecoder.decodeBitmap(source).copy(Bitmap.Config.RGBA_F16, true)

                            val pix = IntArray(bitmap.width * bitmap.height)
                            bitmap.getPixels(pix, 0, bitmap.width, 0, 0, bitmap.width, bitmap.height)

                            makeCircle(pix, bitmap.width, bitmap.height)

                            val out = Bitmap.createBitmap(bitmap.width, bitmap.height, Bitmap.Config.ARGB_8888);
                            out.setPixels(pix, 0, bitmap.width, 0, 0, bitmap.width, bitmap.height);

                            binding.image1.setImageBitmap(out)

                            // Clean up
                            bitmap.recycle()

                        }
                    }
                } catch (e: Exception) {
                    e.printStackTrace()
                    Log.d("TTT", "error: ${e.message}")
                }

            }
        }


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        binding.button1.setOnClickListener {
            openGallery()
        }

    }

    external fun getInfo(): String

    external fun makeCircle(data: IntArray, width: Int, height: Int)

//    external fun ndkEmboss(data: IntArray, width: Int, height: Int)

    private fun openGallery() {
        val intent = Intent()
        intent.type = "image/*"
        intent.action = Intent.ACTION_PICK

        resultLauncher.launch(Intent.createChooser(intent, "Select Picture"))
    }


}
