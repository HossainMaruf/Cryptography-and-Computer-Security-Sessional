x_in = 'x^3+2x-3'
y_in = 'x^2+1'
print('f(x)= '+x_in)
print('g(x)= '+y_in)

# x_in = input("Enter f(x): ")
# y_in = input("Enter g(x): ")

def equ_to_dic(x):
    x = x.split('-')
    for i in range(1,len(x)):
        x[i] = '-' + x[i]
    if '' in x:
        x.remove('')
    x1= list()
    for i in x:
        for j in i.split('+'):
            x1.append(j)

    x_dic =dict()
    for exp in x1:
        if ('x^' not in exp) and ('x' not in exp):
            x_dic[0] = int(exp)
        elif 'x^' not in exp:
            if exp.split('x')[0] == '':
                x_dic = 1
            else:
                x_dic[1] = int(exp.split('x')[0])
        else:
            if exp.split('x^')[0] == '':
                x_dic[int(exp.split('x^')[1])] = 1
            else:
                x_dic[int(exp.split('x^')[1])] = int(exp.split('x^')[0])
    return x_dic


def display(result):
    result_key = list(result.keys())
    result_key.sort(reverse=True)
    ans = ''
    for el in result_key:
        if result[el] > 0:
            co = "+" + str(result[el])
        else:
            co = str(result[el])
        ans = ans + co +'x^'+ str(el)

    if ans[0] == '+':
        ans = ans[1:]
    if ans[-3:] == 'x^0':
        ans = ans[:-3]
    return ans

def add(a,b):
    x = equ_to_dic(a)
    y = equ_to_dic(b)
    sum = dict()
    sum = y
    for element in x.keys():
        if element not in sum.keys():
            sum[element] = x[element]
        else:
            sum[element] = sum[element] + x[element]
    print('summation: ')
    x = equ_to_dic(a)
    sum1 = display(x)
    y = equ_to_dic(b)
    sum2 = display(y)
    print("=("+sum1 + ")" + ' + ' + "("+ sum2 + ")")
    print("="+sum1 + '+' + sum2 )
    print("=" + display(sum))

add(x_in, y_in)


def minus(a, b):
    x = equ_to_dic(a)
    y = equ_to_dic(b)
    sub = dict()
    sub = x
    for element in y.keys():
        if element not in sub.keys():
            sub[element] = y[element]*(-1)
        else:
            sub[element] = sub[element] - y[element]
    print("subtraction: ")
    x = equ_to_dic(a)
    sub1 = display(x)
    y = equ_to_dic(b)
    sub2 = display(y)
    print("=(" + sub1 + ")" + ' - ' + "(" + sub2 + ")")
    sub3 = ''
    for i in sub2:
        if i == '-':
            sub3 = sub3 + '+'
        elif i == '+':
            sub3 = sub3 + '-'
        else:
            sub3 = sub3 + i
    print("=" + sub1 + '-' + sub3)
    print("=" + display(sub))

minus(x_in, y_in)


def multiplication(a, b):
    x = equ_to_dic(a)
    y = equ_to_dic(b)
    mul = dict()
    print('Multiplication: ')
    x = equ_to_dic(a)
    mul1 = display(x)
    y = equ_to_dic(b)
    mul2 = display(y)
    print("=(" + mul1 + ")" + ' * ' + "(" + mul2 + ")")
    print("=", end='')
    for i in x.keys():
        for j in y.keys():
            k = i + j
            if x[i]*y[j] > 0:
                print('+' + str(x[i] * y[j]) + 'x^' + str(k), end='')
            else:
                print(str(x[i]*y[j]) + 'x^' + str(k), end='')
            if k not in mul.keys():
                mul[k] = x[i]*y[j]
            else:
                mul[k] = mul[k] + x[i]*y[j]
    print("\n=" + display(mul))

multiplication(x_in, y_in)