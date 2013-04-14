from utils import Vector2f

class vaisseau:
	
	def __init__(self, ID):
		self.ID = ID
		self.ShapeID = 0
		
		self.Bound = Vector2f(10, 10)
		self.Color = 0x00ff00
		self.Pos = Vector2f(20, 5)
		self.Speed = Vector2f(5, 0)
	
	def __init__(self, id, shapeID, bound, color, pos, speed):
		self.ID = id
		self.ShapeID = shapeID
		
		self.Bound = bound
		self.Color = color
		self.Pos = pos
		self.Speed = speed
	
	def setPosition(x, y):
		self.PosX = x
		self.PosY = y
	
	def setSpeed(x, y):
		self.SpeedX = x
		self.SpeedY = y
	
	def setColor(Color):
		self.Color = Color
	
	def getID():
		return self.ID
	
	def getPositionX():
		return self.PosX
	
	def getPositionY():
		return self.PosY
	
	def getSpeedX():
		return self.SpeedX

	def getSpeedY():
		return self.SpeedY
	
	def getColor():
		return Color
	
	def Move():
		self.PosX = self.SpeedX
		self.PosY = self.SpeedY
