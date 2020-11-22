Level = {}

function Level._updateCall()

	Level.Update()

	for _,actor in pairs(actors) do
		actor:_update()
	end

end

function Level._unloadCall()

	Level.OnUnload()

	Level.OnLoad = function()end
	Level.OnUnload = function()end
	Level.Update = function()end
	Level.OnQuit = function()end

end

return Level