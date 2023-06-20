package com.example.betting

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.example.betting.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

//        // Example of a call to a native method
//        binding.sampleText.text = stringFromJNI()
//        binding.sampleText.text = process()

        binding.btnCalculate.setOnClickListener {
            val pLose = calculatePLose()
            val roi = calculateROI()
            val ev = calculateEV()
            val bankrollPercentage = calculateBankrollPercentage()
            val bet = calculateBet()

            binding.tvPLose.text = getString(R.string.label_p_lose, pLose)
            binding.tvROI.text = getString(R.string.label_roi, roi)
            binding.tvEV.text = getString(R.string.label_ev, ev)
            binding.tvBankrollPercentage.text = getString(R.string.label_bankroll_percentage, bankrollPercentage)
            binding.tvBet.text = getString(R.string.label_bet, bet)        }
    }

    /**
     * A native method that is implemented by the 'betting' native library,
     * which is packaged with this application.
     */
//    external fun stringFromJNI(): String
//    fun processInJava(): String {
//        return "Processed in Java"
//    }
    fun getBankroll() = binding.etBankroll.text.toString().toDouble()
    fun getPWin() = binding.etPWin.text.toString().toDouble()
    fun getOdds() = binding.etOdds.text.toString().toDouble()
//    external fun process(): String

    private external fun calculatePLose(): Double
    private external fun calculateROI(): Double
    private external fun calculateEV(): Double
    private external fun calculateBankrollPercentage(): Double
    private external fun calculateBet(): Double

    companion object {
        // Used to load the 'betting' library on application startup.
        init {
            System.loadLibrary("betting")
        }
    }
}