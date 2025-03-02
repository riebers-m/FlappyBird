function setup()
    print("Setup function called")
end

function update(dt)
    local ddt = dt - 5
    print("Update function called with ddt: " .. ddt)
end
