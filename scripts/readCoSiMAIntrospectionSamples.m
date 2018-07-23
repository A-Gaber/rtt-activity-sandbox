fname = "../build/orocos/rtReport.dat"; 
fid = fopen(fname); 
raw = fread(fid,inf); 
str = char(raw'); 
fclose(fid); 
val = jsondecode(str);

amountOfData = size(val.root);
amountOfData = amountOfData(1);

updateContainer_M = [];
updateContainer_S = [];
updateContainer_R = [];

for index = 1:amountOfData
    item = val.root(index);
    if strcmp(item.call_name, 'updateHook()') == 1
        
        if strcmp(item.container_name, 'M') == 1
             %disp(item)
            tmp=[double(item.call_time), 0; double(item.call_time), 1; double(item.call_duration), 1; double(item.call_duration), 0];
            updateContainer_M = cat(1, updateContainer_M, tmp);
        elseif strcmp(item.container_name, 'S') == 1
            tmp=[double(item.call_time), 0; double(item.call_time), 1; double(item.call_duration), 1; double(item.call_duration), 0];
            updateContainer_S = cat(1, updateContainer_S, tmp);
        elseif strcmp(item.container_name, 'R') == 1
            tmp=[double(item.call_time), 0; double(item.call_time), 1; double(item.call_duration), 1; double(item.call_duration), 0];
            updateContainer_R = cat(1, updateContainer_R, tmp);
        end
    end
end

% get the maximum time
mM = max(updateContainer_M(:,1));
mS = max(updateContainer_S(:,1));
mR = max(updateContainer_R(:,1));
mMaxTime = max(mM, max(mS, mR));

figure
ax1 = subplot(3,1,1);
plot(ax1, updateContainer_M(:,1), updateContainer_M(:,2), '-.or')
title(ax1,'Execution of M')
%ylabel(ax1,'Values from -1 to 1')

ax2 = subplot(3,1,2);
plot(ax2, updateContainer_S(:,1), updateContainer_S(:,2), '-.og')
title(ax2,'Execution of S')
%ylabel(ax2,'Values from 0 to 1')

ax3 = subplot(3,1,3);
plot(ax3, updateContainer_R(:,1), updateContainer_R(:,2), '-.ob')
title(ax3,'Execution of R')
%ylabel(ax3,'Values from 0 to 1')

linkaxes([ax1,ax2,ax3],'x')
