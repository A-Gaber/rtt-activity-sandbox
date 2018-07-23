fname = "../scripts/results/rtReport-verify-message-passing-ms.dat"; 
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
updateContainer_M2 = [];
updateContainer_S2 = [];

read_new_R = [];
read_old_R = [];
write_S2 = [];

for index = 1:amountOfData
    item = val.root(index);
    if strcmp(item.call_name, 'updateHook()') == 1
        tmp=[double(item.call_time), 0; double(item.call_time), 1; double(item.call_duration), 1; double(item.call_duration), 0];
        if strcmp(item.container_name, 'M') == 1
             %disp(item)
            updateContainer_M = cat(1, updateContainer_M, tmp);
        elseif strcmp(item.container_name, 'S') == 1
            updateContainer_S = cat(1, updateContainer_S, tmp);
        elseif strcmp(item.container_name, 'R') == 1
            updateContainer_R = cat(1, updateContainer_R, tmp);
       elseif strcmp(item.container_name, 'M2') == 1
            updateContainer_M2 = cat(1, updateContainer_M2, tmp);
        elseif strcmp(item.container_name, 'S2') == 1
            updateContainer_S2 = cat(1, updateContainer_S2, tmp);
        end
    elseif strcmp(item.call_type, 'CALL_PORT_READ_NEWDATA') == 1
        if strcmp(item.container_name, 'R') == 1
            tmp=[double(item.call_time), 0.8];
            read_new_R = cat(1, read_new_R, tmp);
        end
    elseif strcmp(item.call_type, 'CALL_PORT_READ_OLDDATA') == 1
        if strcmp(item.container_name, 'R') == 1
            tmp=[double(item.call_time), 0.5];
            read_old_R = cat(1, read_old_R, tmp);
        end
    elseif strcmp(item.call_type, 'CALL_PORT_WRITE') == 1
        if strcmp(item.container_name, 'S2') == 1
            tmp=[double(item.call_time), 0.2];
            write_S2 = cat(1, write_S2, tmp);
        end
    end
end

% get the maximum time
mM = max(updateContainer_M(:,1));
mS = max(updateContainer_S(:,1));
mR = max(updateContainer_R(:,1));
mM2 = max(updateContainer_M2(:,1));
mS2 = max(updateContainer_S2(:,1));
mMaxTime = max(mS2, max(mM2, max(mM, max(mS, mR))));

figure
ax1 = subplot(5,1,1);
plot(ax1, updateContainer_M(:,1), updateContainer_M(:,2), '-.or')
title(ax1,'Execution of M')
%ylabel(ax1,'Values from -1 to 1')

ax2 = subplot(5,1,2);
plot(ax2, updateContainer_S(:,1), updateContainer_S(:,2), '-.og')
title(ax2,'Execution of S')
%ylabel(ax2,'Values from 0 to 1')

ax3 = subplot(5,1,3);
hold on
plot(ax3, updateContainer_R(:,1), updateContainer_R(:,2), '-.ob')
plot(ax3, read_new_R(:,1), read_new_R(:,2), '-wo',...
                'LineWidth',0.001,...
                'MarkerEdgeColor','m',...
                'MarkerSize',5)
old_size = size(read_old_R);
old_size = old_size(1);
if old_size > 0
plot(ax3, read_old_R(:,1), read_old_R(:,2), '-wo',...
                'LineWidth',0.001,...
                'MarkerEdgeColor','r',...
                'MarkerSize',5)
end
hold off
title(ax3,'Execution of R')
%ylabel(ax3,'Values from 0 to 1')

ax4 = subplot(5,1,4);
plot(ax4, updateContainer_M2(:,1), updateContainer_M2(:,2), '-.or')
title(ax4,'Execution of M2')

ax5 = subplot(5,1,5);
hold on
plot(ax5, updateContainer_S2(:,1), updateContainer_S2(:,2), '-.og')
plot(ax5, write_S2(:,1), write_S2(:,2), '-wo',...
                'LineWidth',0.001,...
                'MarkerEdgeColor','k',...
                'MarkerSize',5)
hold off
title(ax5,'Execution of S2')

linkaxes([ax1,ax2,ax3,ax4,ax5],'x')
