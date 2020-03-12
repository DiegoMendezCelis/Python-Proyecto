
import sys                                            
import paho.mqtt.client
import RPi.GPIO as gpio
gpio.setwarnings(False)
gpio.setmode(gpio.BCM)
gpio.setup(27,gpio.OUT)
gpio.setup(17,gpio.OUT)



from prefinal import *
luza=0
luzb=0

captura=" "
comparacion1=b'abierto'
comparacion2=b'cerrado'
estadolaba="lab abierto"
estadolab="lab cerrado"


a=15
b=str(a)

def on_connect(client, userdata, flags, rc):
    client.subscribe(topic='laboratorio/iluminacion', qos=2)
 
def on_message(client, userdata, message):
    
    print( message.payload)
    global captura
    captura=message.payload
    print (b)
    if (captura==comparacion1):
        b="lab abierto"
        self.temperatura_2.setText(b)
        print("lab abierto")
    
    else:
        pass
    if(captura==comparacion2):
        b = "lab cerrado"
        self.temperatura_2.setText(b)
        print("lab cerrado")
     
    else:
        pass

    
class MainWindow(QtWidgets.QMainWindow,Ui_MainWindow):
   
 
    def __init__(self, *args, **kwargs):
        QtWidgets.QMainWindow.__init__(self, *args, **kwargs)
        self.setupUi(self)
        client = paho.mqtt.client.Client(client_id='andres', clean_session=False)
        client.on_connect = on_connect
        client.on_message = on_message
        client.connect(host='localhost', port=1883)
        client.loop_start()
        
        self.luz.setText(b)
        self.temperatura_2.setText(b)
        self.salen.setText(b)
        self.entran.setText(b)
        self.adentro.setText(b)
        
        self.encendidoaire.clicked.connect(self.aireon)
        self.arribaaire.clicked.connect(self.airearriba)
        self.abajoaire.clicked.connect(self.aireabajo)
        self.encendidotv .clicked.connect(self.tvon)
        self.canalmas.clicked.connect(self.tvmas)
        self.canalmenos.clicked.connect(self.tvmenos)
        self.volumenmas.clicked.connect(self.tvvolmas)
        self.volumenmenos.clicked.connect(self.tvvolmenos)
        self.salen.setText(b)
        self.entran.setText(b)
        self.adentro.setText(b)
        self.labsdos.clicked.connect(self.luz2)
        self.labsuno.clicked.connect(self.luz1)
       

    def aireon(self):
        self.luz.setText(b)
    def airearriba(self):
        self.luz.setText(b)
    def aireabajo(self):
        self.luz.setText(b)
    def tvon(self):
        self.luz.setText(b)
    def tvmas(self):
        self.luz.setText(b) 
    def tvmenos(self):
        self.luz.setText(b)
    def tvvolmas(self):
          self.luz.setText(b)
    def tvvolmenos(self):
        self.luz.setText(b)
   
    def luz1(self):
        global luza
        if (luza%2==0):
            gpio.output(27,True)
        else:
            gpio.output(27,False)
        luza=luza+1
        print(luza)

    def luz2(self):
        global luzb
        if (luzb%2==0):
            gpio.output(17,True)
        else:
            gpio.output(17,False)
        luzb=luzb+1
        print(luzb)



        
  
     
if __name__=="__main__":
    app=QtWidgets.QApplication([])
    window=MainWindow()
    window.show()
    app.exec_()
    
    
