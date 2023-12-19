function  x_new =fast(x_value)
    x = sym('x',[1,10]);
    syms t;
    f = get_f();
    % 获得函数的一阶导数dx
    dx = subs(df1(),x,x_value);
    % 求最佳步长
    m = x_value - t * dx;
    % disp(m);
    fun_t = subs(f,x,m);
    % disp(fun_t);
    diff_t = diff(fun_t);
    % disp(diff_t);
    t_all = real(double(solve(diff_t)));
    % disp(t_all);
    t_1 = t_all(1);
    x_new = double(subs(m,t,t_1));
    y_new = double(subs(f,x,x_new));
    for i = 1:length(t_all)
        x_test = double(subs(m,t,t_all(i)));
        y_test = double(subs(f,x,x_test));
        if(y_test < y_new)
            x_new = x_test;
            y_new = y_test;
        end
    end
    disp(y_new);
end