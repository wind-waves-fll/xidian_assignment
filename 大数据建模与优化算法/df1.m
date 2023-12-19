function dx = df1()
    f = get_f();
    x = sym('x',[1,10]);
    for i=1:10
        dx(i) = diff(f,x(i));
    end
end