import datetime

def Afficher(type, message):
    now = datetime.date.today()
    print("[" + now.ctime() + "]" + "[" + type + "]" + message)
    
def Info(message):
    Afficher("Info", message) 
    
def Alert(message):
    Afficher("Info", message) 

def FixMe(message):
    Afficher("Info", message) 