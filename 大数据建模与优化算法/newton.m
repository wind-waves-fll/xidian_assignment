function  x_new =newton(x_value)
    x = sym('x',[1,10]);
    syms t;
    f = get_f();
    dx = subs(df1(),x,x_value);
    d2x = subs(df2(),x,x_value);
    d2x_1 = inv(d2x);
    % 下降方向d
    d = - d2x_1 * dx.';
    % 求最佳步长
    m = x_value - t * d.';
    fun_t = subs(f,x,m);
    diff_t = diff(fun_t);
    t_all = real(double(solve(diff_t)));
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