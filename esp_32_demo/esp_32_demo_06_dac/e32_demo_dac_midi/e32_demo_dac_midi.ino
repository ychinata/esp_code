#include <Arduino.h>

uint16_t lFre[]{262, 294, 330, 349, 392, 440, 494};         //C调低音1-7的频率
uint16_t mFre[]{523, 587, 659, 698, 784, 880, 988};         //C调中音1-7的频率
uint16_t hFre[]{1047, 1175, 1319, 1397, 1568, 1760, 1967};  //C调高音1-7的频率

int pos = 0;

hw_timer_t * mytimer;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

//计算正弦所要的
double w = 0;
double a = 50;
uint8_t c = 127;
uint64_t count = 0;

uint16_t baseDuration = 1000;     //一拍1S

struct Midi {
	uint8_t Scale;     //音阶 1-7 中音， 11- 17 低音 21-27高音
	uint8_t Duration;  //节拍数 1:1拍  2：1/2   4: 1/4   5:3/4
};

//两只老虎
Midi tiger[]{
	{1, 2}, {2, 2}, {3, 2}, {1, 2},   {1, 2}, {2, 2}, {3, 2}, {1, 2},
	{3, 2}, {4, 2}, {5, 2}, {0, 2},   {3, 2}, {4, 2}, {5, 2}, {0, 2},
	{5, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 2}, {1, 2},    {5, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 2}, {1, 2},
	{1, 2}, {15, 2}, {1, 5}, {0, 4},     {1, 2}, {15, 2}, {1, 5}, {0, 4},
	{0, 1}, {0, 1}
};

void IRAM_ATTR timer_isr()
{
	portENTER_CRITICAL_ISR(&mux);
	if (w == 0) {
	  	dacWrite(25, 0);
	} else {
		double t = count++ * 100e-6;
		uint8_t val = a*sin(w*t)+c;
		dacWrite(25, val);
	}
	portEXIT_CRITICAL_ISR(&mux);
}

//播放一个音符，使用dac输出
void PlayMusicScaleDac(const Midi& mid)
{
	uint32_t fre = 0;
	uint32_t duration = 1000;
	
	if(mid.Duration == 2)
		duration = 500;
	else if(mid.Duration == 4)
		duration = 250;
	else if(mid.Duration == 5)
		duration = 750;

	if(mid.Scale == 0)
		fre = 0;
	else if(mid.Scale < 10)  //是中音
		fre = mFre[mid.Scale-1];
	else if(mid.Scale < 20) //是低音
		fre = lFre[mid.Scale - 11];
	else if(mid.Scale < 30)
		fre = hFre[mid.Scale - 21];

	portENTER_CRITICAL(&mux);

	if(fre == 0)
		w = 0;
	else
		w = fre * 2*3.14159265;
	count = 0;
	portEXIT_CRITICAL(&mux);

	delay(duration);
}

void setup() {
	Serial.begin(115200);

	mytimer = timerBegin(0, 80, true);
	timerAttachInterrupt(mytimer, timer_isr, true);

	//100us触发一次
	timerAlarmWrite(mytimer, 100, true);

	//开启定时器
	timerAlarmEnable(mytimer);

}

void loop() {
	if(pos >= sizeof(tiger)/sizeof(Midi))
		pos = 0;
	PlayMusicScaleDac(tiger[pos++]);
}

