#include <IRremote.h>
#include <SoftwareSerial.h>
SoftwareSerial master (4,5);
String stream;


unsigned int power[] = {4550,4400,600,1650,550,1650,600,1650,
550,550,600,500,600,550,550,550,600,500,600,1650,600,1600,600,
1650,550,550,600,500,600,550,600,500,600,500,650,450,650,1600,
600,500,650,450,650,500,600,500,600,500,600,550,600,1600,600,
500,650,1600,650,1550,650,1600,650,1550,650,1600,650,1600,600};

unsigned int volumeup[] = {4586,4444,612,1624,612,1624,612,1626,610,486,634,506,612,508,612,506,638,480,612,1626,612,1624,614,1626,610,508,610,486,634,506,612,508,610,508,638,1600,612,1626,612,1604,634,506,612,508,610,486,632,508,612,506,612,508,610,508,612,508,610,1628,610,1628,610,1626,612,1626,610,1628,610,48510,364,906,260,438,284,688,342};
unsigned int volumedown[] = {4532,4496,612,1626,558,1658,632,1628,610,510,610,508,610,510,608,510,610,508,610,1628,610,1628,558,1680,610,510,610,508,558,562,556,562,610,506,558,1682,610,1626,608,510,608,1630,610,508,556,562,610,508,610,508,558,560,612,508,610, 1628,608,512,610,1626,610,1628,610,1628,610,1628,556};
unsigned int source[] = {13018,4450,-4500,550,-1650,550,-1650,550,-1700,550,-550,550,-550,550,-550,550,-550,550,-600,550,-1650,550,-1650,550,-1700,550,-550,550,-550,550,-550,550,-550,550,-550,600,-1650,550,-550,550,-550,550,-550,550,-600,550,-550,550,-550,550,-550,550,-550,550,-1700,550,-1650,550,-1650,550,-1650,600,-1650,550,-1650,550,-1700,550 
};
unsigned int Chplus[] = {9074,4414,582,542,610,1630,612,512,582,540,582,542,582,542,582,540,582,542,612,1628,584,542,612,514,582,1656,610,1628,610,1632,582, 1660,582,1658,582,542,612,1628,582,1656,582,1658,582,1658,584,540,584,1658,584,540,582,1634,634,514,582,542,582,540,582,542,610,1630,582,542,582,1658,582};
unsigned int Chminus[] = {9016,4472,582,544,582,1660,634,490,582,542,582,544,580,542,634,490,582,520,606,1660,582,544,634,466,606,1658,582,1658,582,1638,604,1660,582,1660,582,1660,582,1660,634,1608,632,1608,582,1660,582,544,634,1584,656,490,582,544,580,540,582,544,582,520,604,542,582,1660,582,542,634,1606,582};

unsigned int mute[] = {4566,4442,612,1626,612,1626,612,1624,612,506,612,506,612,506,612,506,612,508,612,1624,614,1624,612,1624,614,506,612,506,612,506,612,506,612,506,612,1626,612,1624,614,1624,612,1626,612,506,612,506,612,506,612,506,612,506,612,506,612,508,638,480,614,1626,612,1626,612,1626,612,1626,612};

unsigned int settings[] = {27968,4550,-4400,600,-1650,550,-1650,600,-1600,600,-500,650,-500,550,-550,600,-500,600,-500,600,-1650,600,-1600,550,-1650,600,-550,600,-500,600,-500,600,-500,600,-500,600,-500,600,-1650,600,-500,600,-1600,600,-1650,600,-500,600,-500,600,-500,600,-1650,600,-500,600,-1600,600,-500,600,-550,600,-1600,650,-1550,600,-1650,600 
};

unsigned int enter[] = {10444,4500,-4450,550,-1650,550,-1700,550,-1650,600,-500,550,-600,550,-550,550,-550,550,-550,550,-1650,550,-1700,550,-1650,550,-550,550,-600,550,-550,550,-550,550,-550,550,-550,550,-550,600,-550,550,-1650,550,-550,550,-1700,550,-1650,550,-550,550,-1650,550,-1700,550,-1650,550,-550,550,-1700,550,-550,550,-550,600,-1600,550 
};

unsigned int homee[] = {22518,4550,-4400,600,-1600,600,-1650,600,-1600,600,-500,600,-500,600,-500,600,-550,600,-500,600,-1600,600,-1600,650,-1600,600,-500,600,-500,600,-500,600,-550,600,-500,600,-1600,550,-550,600,-500,600,-1650,600,-1600,600,-1650,650,-1550,600,-500,600,-500,600,-1650,600,-1600,600,-500,600,-500,600,-500,650,-500,600,-1600,600 
};

unsigned int exitt[] = {27940,4500,-4450,600,-1600,550,-1650,550,-1700,550,-550,550,-550,550,-550,550,-550,550,-600,550,-1650,550,-1650,550,-1700,550,-550,550,-550,600,-500,600,-500,550,-600,600,-1600,550,-550,550,-1650,550,-1700,550,-550,550,-1650,550,-600,550,-550,550,-550,550,-1650,550,-550,600,-550,550,-1650,550,-550,550,-1650,600,-1650,550 
};
IRsend irsend;
void setup()
{
  pinMode (3, OUTPUT);  //output used in library
   Serial.begin(9600);
   master.begin(115200);
}
void loop() {
  if (master.available()){
    stream = master.readStringUntil('\n');
    stream.trim();
    if (stream.length()>0){
      if (stream == "power"){
      irsend.sendRaw(power,68,38);
      Serial.print("power");
      }
      else if (stream == "homee"){
        irsend.sendRaw(homee,68,38);
      }
      else if (stream == "volumeup"){
        irsend.sendRaw(volumeup,75,38);
      }
      else if (stream == "volumedown"){
        irsend.sendRaw(volumedown,68,38);
      }
      else if (stream == "mute"){
        irsend.sendRaw(mute,67,38);
      }
      else if (stream == "exitt"){
        irsend.sendRaw(exitt,68,38);
      }
      else if (stream == "settings"){
        irsend.sendRaw(settings,68,38);
      }
      else if (stream == "Chplus"){
        irsend.sendRaw(Chplus,68,38);
      }
      else if (stream == "Chminus"){
        irsend.sendRaw(Chminus,68,38);
      }
      else if (stream == "volpl"){
        irsend.sendNEC(0x90FD1BE4, 32);
      }
      else if (stream == "volmin"){
        irsend.sendNEC(0x90FDDB24, 32);
      }
      else if (stream == "chpl"){
        irsend.sendNEC(0x90FD7B84, 32);
      }
      else if (stream == "chmin"){
        irsend.sendNEC(0x90FD6B94, 32);
      }
      else if (stream == "ok"){
        irsend.sendNEC(0x90FD5BA4, 32);
      }
      Serial.println(stream);
      stream="";
    }

      
    }

}