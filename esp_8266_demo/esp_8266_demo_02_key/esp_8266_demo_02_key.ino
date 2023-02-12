
// 2022.12.31
// 参考https://www.bilibili.com/video/BV1gE411D7xP?p=4
// 按键按下,点亮LED, 松开,熄灭LED

int BUTTON = 5;  // IO5, D1
int LED = 14;   // IO14, D5

void setup() {
    // put your setup code here, to run once:
    pinMode(BUTTON, INPUT_PULLUP);  // 设置按键引脚为上拉模式
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);         // 关闭LED
}

void loop() {
    // put your main code here, to run repeatedly:
    if (digitalRead(BUTTON) == LOW) {   // 按键按下，接地为低电平，点亮LED
        digitalWrite(LED, HIGH);
    } else {
        digitalWrite(LED, LOW);
    }

}
