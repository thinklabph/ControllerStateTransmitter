#define DEBUG if (Serial) Serial.print
#define DEBUG_LN if (Serial) Serial.println

#define RF24_ADDRESS "TRC24"

enum pixel_colors{
  RED,
  BLUE,
  GREEN,
  YELLOW,
  OFF
};

// These can be changed freely when using the bitbanged protocol
const byte PIN_PS2_ATT = 2;
const byte PIN_PS2_CMD = 1;
const byte PIN_PS2_DAT = 0;
const byte PIN_PS2_CLK = 3;

long heartbeat_ctr=0;

void print_hex(uint64_t v, int num_places)
{
    int mask=0, n, num_nibbles, digit;

    for (n=1; n<=num_places; n++)
    {
        mask = (mask << 1) | 0x0001;
    }
    v = v & mask; // truncate v to specified number of places

    num_nibbles = num_places / 4;
    if ((num_places % 4) != 0)
    {
        ++num_nibbles;
    }

    do
    {
      digit = ((v >> (num_nibbles-1) * 4)) & 0x0f;
      Serial.print(digit, HEX);
    } while(--num_nibbles);

}

uint64_t new_ctrlr_state=0, cur_ctrlr_state=0;

void setup () {

	Serial.begin (115200);

  // while(!Serial);

  initPixel();
  blink_pixel(BLUE, 0);

  // while(!Serial);
	initRadio(new_ctrlr_state);
  
  DEBUG_LN(F("Ready!"));

    // while(1);
}

void loop() {
	// static byte slx, sly, srx, sry;
	
	// fastDigitalWrite (PIN_HAVECONTROLLER, haveController);
start:
  while (!haveController()) initController();

  if (!psxRead()){
    DEBUG_LN(F("Controller lost :("));
    reuqestControllerInit();
    goto start;
  } 

  cur_ctrlr_state = getControllerState();
  // Serial.println(cur_ctrlr_state);
  // print_hex(new_ctrlr_state, 32);
  if (cur_ctrlr_state!=new_ctrlr_state){
    new_ctrlr_state=cur_ctrlr_state;
    // Serial.println(new_ctrlr_state, HEX);
    print_hex(new_ctrlr_state, 64);
    Serial.println("");
    radioTransmit(new_ctrlr_state);
    blink_pixel(BLUE, 100);
    
  }
  // fastDigitalWrite (PIN_BUTTONPRESS, !!psx.getButtonWord ());

	
	// delay (1000 / 60);
  heartbeat();
}

void heartbeat(){
  heartbeat_ctr++;
  if(heartbeat_ctr>300){
    heartbeat_ctr=0;
    blink_pixel(GREEN, 50);
  }
}
