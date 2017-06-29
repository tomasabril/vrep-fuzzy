
-- Put some initialization code here:
kJunior=simGetObjectHandle('KJunior')
leftAndRightMotorHandles={simGetObjectHandle('KJunior_motorLeft'),simGetObjectHandle('KJunior_motorRight')}
proxSensorHandles={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
--lightSensorHandles={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
for i=1,10,1 do
    proxSensorHandles[i]=simGetObjectHandle('KJunior_proxSensor'..i)
    --lightSensorHandles[i]=simGetObjectHandle('KJunior_lightSensor'..i)
end
sens_UI=simGetUIHandle('KJunior_sens_UI')
simSetUIButtonLabel(sens_UI,0,simGetObjectName(kJunior))



-- Choose a port that is probably not used (try to always use a similar code):
simSetThreadAutomaticSwitch(false)
local portNb= simGetInt32Parameter(sim_intparam_server_port_next)
local portStart=simGetInt32Parameter(sim_intparam_server_port_start)
local portRange=simGetInt32Parameter(sim_intparam_server_port_range)
local newPortNb=portNb+1
if (newPortNb>=portStart+portRange) then
    newPortNb=portStart
end
simSetInt32Parameter(sim_intparam_server_port_next,newPortNb)
--simSetThreadAutomaticSwitch(true)

-- Check what OS we are using:
platf=simGetInt32Parameter(sim_intparam_platform)
if (platf==0) then
    pluginFile='v_repExtRemoteApi.dll'
end
if (platf==1) then
    pluginFile='libv_repExtRemoteApi.dylib'
end
if (platf==2) then
    pluginFile='libv_repExtRemoteApi.so'
end

-- Check if the required remote Api plugin is there:
moduleName=0
moduleVersion=0
index=0
pluginNotFound=true
while moduleName do
    moduleName,moduleVersion=simGetModuleName(index)
    if (moduleName=='RemoteApi') then
        pluginNotFound=false
    end
    index=index+1
end

if (pluginNotFound) then
    -- Plugin was not found
    simDisplayDialog('Error',"Remote Api plugin was not found. ('"..pluginFile.."')&&nSimulation will not run properly",sim_dlgstyle_ok,true,nil,{0.8,0,0,0,0,0},{0.5,0,0,1,1,1})
else
    -- Ok, we found the plugin.
    -- We first start the remote Api server service (this requires the v_repExtRemoteApi plugin):
    simExtRemoteApiStart(portNb) -- this server function will automatically close again at simulation end

    -- Now we start the client application:
    result=simLaunchExecutable('fuzzyKJunior',portNb.." "..leftAndRightMotorHandles[1].." "..leftAndRightMotorHandles[2].." "..proxSensorHandles[1].." "..proxSensorHandles[2].." "..proxSensorHandles[3].." "..proxSensorHandles[4].." "..proxSensorHandles[5].." "..proxSensorHandles[6].." "..proxSensorHandles[7].." "..proxSensorHandles[8].." "..proxSensorHandles[9].." "..proxSensorHandles[10],0) -- set the last argument to 1 to see the console of the launched client

    if (result==-1) then
        -- The executable could not be launched!
        simDisplayDialog('Error',"'bubbleRobClient' could not be launched. &&nSimulation will not run properly",sim_dlgstyle_ok,true,nil,{0.8,0,0,0,0,0},{0.5,0,0,1,1,1})
    end
end






-- Here we execute the regular thread code:
res,err=xpcall(threadFunction,function(err) return debug.traceback(err) end)
if not res then
    simAddStatusbarMessage('Lua runtime error: '..err)
end
