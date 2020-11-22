local actor

function OnLoad()

	actor = Actor.new("Joe")
	rend = actor:AddComponent(ComponentType.SpriteRenderer)
	rend:SetSprite("sprite.jpg")
	rend.colour = Colour.blue
	rend:SetSprite("sprite.jpg")
	rend:SetSprite(nil)
end

function Update()

	local x = 0
	local speed = 5

	if(Input.GetKeyState(KeyCode.ArrowLeft) == KeyState.Down) then
		x = x - 1
	end
	
	if(Input.GetKeyState(KeyCode.ArrowRight) == KeyState.Down) then
		x = x + 1
	end
	
	actor.transform.position.x = actor.transform.position.x + x*speed
	
end

function OnUnload()

	error("aww poo im unloading")
	
end

Level.OnLoad = OnLoad
Level.Update = Update
Level.OnUnload = OnUnload