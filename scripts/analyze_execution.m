input = dlmread("../build/orocos/tc_slave_one_master.dat");
inputS = dlmread("../build/orocos/tc_slave_one_master_s.dat");
inputR = dlmread("../build/orocos/tc_slave_one_master_r.dat");

subplot (3, 1, 1)
plot(input(:,1),input(:,2));
subplot (3, 1, 2)
#plot(input(:,1),input(:,3));
plot(inputS(:,1),inputS(:,2));
subplot (3, 1, 3)
#plot(input(:,1),input(:,4));
plot(inputR(:,1),inputR(:,2));