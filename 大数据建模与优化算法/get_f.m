function f = get_f()
    x = sym('x',[1,10]);
    f = 0;
    for i = 1:9
        f = f + (1-x(i))^2 +100*(x(i+1)-x(i)^2)^2;
    end
end
