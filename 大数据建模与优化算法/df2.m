function d2x = df2()
    x = sym('x',[1,10]);
    dx = df1();
    for i = 1:10
        for j = 1:10
            d2x(i,j) = diff(dx(i),x(j));
        end
    end
end