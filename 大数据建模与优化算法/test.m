x_value = [0,0,0,0,0,0,0,0,0,0];
tic
for i =1:10
    x_value = fast(x_value);
end
toc
disp(['运行时间: ',num2str(toc)]);