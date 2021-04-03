const char* myAPN = "hologram";
const char* mqttURL = "iot.cuspix.com";
const char* mqttPort = "1883";
//String urlStr ="iot.cuspix.com";
//String portStr= "1883";

void SIM7080_tcpSend(String tcpData,String tcpUrl,String tcpPort){
  char dataStruct[256];
 int dataLen = 0;
 char cmdStruct[64];
 char urlStruct[64];


  dataLen=tcpData.length() + 1;
 tcpData.toCharArray(dataStruct,dataLen);
String tcpCmdStr= "AT+CASEND=0,"+ String(dataLen);
 String tcpUrlStr= "AT+CAOPEN=0,0,\"TCP\",\"" + tcpUrl +"\"," + tcpPort;
 tcpUrlStr.toCharArray(urlStruct, tcpUrlStr.length() + 1);
 tcpCmdStr.toCharArray(cmdStruct, tcpCmdStr.length() + 1);
  fona.sendCheckReply("AT+CNCFG=0,1,\"hologram\"","OK",1000);
  fona.sendCheckReply("AT+CNACT=0,1","OK",1000);
  fona.sendCheckReply("AT+CNACT?","OK",1000);
  fona.sendCheckReply("AT+CASSLCFG=0,\"SSL\",0","OK", 1000);

  fona.sendCheckReply(urlStruct,"OK",1000);
  //fona.sendCheckReply("AT+CAOPEN=0,0,\"TCP\",\"69.137.63.201\",9600","OK",1000);
  
  fona.sendCheckReply(cmdStruct,">",1000);
  //fona.sendCheckReply("AT+CASEND=0,10",">",1000);
  fona.sendCheckReply(dataStruct,"OK",1000);
 // fona.sendCheckReply("HELLO BILL","OK",1000);
  fona.sendCheckReply("AT+CACLOSE=0","OK",1000);
  fona.sendCheckReply("AT+CNACT=0,0","OK",1000);
  

  }



void SIM7080_mqttPubData(String pubTopic,String pubMsg, String urlStr, String portStr){
 char dataStruct[256];
 int dataLen = 0;
 char cmdStruct[64];
 char urlStruct[64];
 
 dataLen=pubMsg.length() + 1;
 pubMsg.toCharArray(dataStruct,dataLen);
 String pubCmdStr= "AT+SMPUB=\"" + pubTopic + "\"," + String(dataLen) + ",0,0";
 String pubUrlStr= "AT+SMCONF=\"URL\",\"" + urlStr +"\"," + portStr;
 pubUrlStr.toCharArray(urlStruct, pubUrlStr.length() + 1);
 pubCmdStr.toCharArray(cmdStruct, pubCmdStr.length() + 1);
 fona.sendCheckReply("AT+CNCFG=0,1,\"hologram\"","OK",1000);
 fona.sendCheckReply("AT+CNACT=0,1","OK",1000);
 fona.sendCheckReply("AT+CNACT?","OK",1000);
 
 //fona.sendCheckReply("AT+SMCONF=\"URL\",\"iot.cuspix.com\",1883","OK", 1000);
 fona.sendCheckReply(urlStruct,"OK",1000);
 fona.sendCheckReply("AT+SMCONF=\"KEEPTIME\",60","OK",1000);  
 fona.sendCheckReply("AT+SMCONF=\"CLEANSS\",1","OK",1000);
 fona.sendCheckReply("AT+SMCONN","OK",3000);
 fona.sendCheckReply(cmdStruct,">",1000);
 fona.sendCheckReply(dataStruct,"OK",1000); 
 fona.sendCheckReply("AT+SMDISC","OK",1000);
 fona.sendCheckReply("AT+CNACT=0,0","OK",500);
 delay(1000);
  
}

String SIM7080_getDateTime(){
  char buffer[23];
  String tString = "";
 
  
  fona.getTime(buffer, 23);  // make sure replybuffer is at least 23 bytes!
  tString = String(buffer);
  tString.remove(0,1);
  int x = tString.length();
  tString.remove(x-1,1);   
    return tString;      
}
