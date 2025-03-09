function Setup()
    print("Setup function called")
    ballPosition = Vec2.new(100, 200)
end

function Update(dt)
    print("ball pos: ", ballPosition.x, ";", ballPosition.y)
end
