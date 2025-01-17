import numpy
import pandas as pd
import random

# Cache
l4 = [0 for i in range(4096)]
l3 = [[-1, -1] for i in range(2) for j in range(128)]  # 아무것도 없는 상태 = -1 임
l2 = [0 for i in range(16)]
l1 = [0, ]

# 주소 클래스, 각 계층에 저장될 애들, 실제 데이터를 찾고 싶다면 주소 클래스의 bit와 데이터클래스의 bit 비교  
    
class address():
    def __init__(self): # 32 bit
        self.tag = random.getrandbits(21)  # 21bit
        self.index = random.getrandbits(8)  # 0~256 : 0 ~ 2^8-1, 8 bit
        self.offset = random.randrange(0,12)  # 0~7 : 0~2^3-1, 3 bit
        num1 = bin(self.offset)[2:]
        num2 = bin(self.index)[2:]
        num3 = bin(self.tag)[2:]
        self.bit = int(num3 + num2 + num1)

    def getOffset(self, tag, index):
        return self.offset

    def info(self):
        print(self.tag, self.index, self.offset)

    def getBit(self):
        num1 = bin(self.offset)[2:]
        num2 = bin(self.index)[2:]
        num3 = bin(self.tag)[2:]
        bitNum = num3 + num2 + num1  # bin을 이용하면 str타입임
        return int(bitNum)  # str -> int

    def getAddr(self):
        return (str(self.tag) + str(self.index) + str(self.offset))


# 데이터 클래스 : 주소 + 데이터
class data():
    def __init__(self, dt):
        self.address = address()  # 주소
        self.dt = dt  # real data

        num1 = bin(self.address.offset)[2:]
        num2 = bin(self.address.index)[2:]
        num3 = bin(self.address.tag)[2:]
        self.bit = int(num3 + num2 + num1)  # bin을 이용하면 str타입임

    def printData(self,offset):
        print("data : ", str(self.dt[offset]))

    def getBit(self):
        num1 = bin(self.address.offset)[2:]
        num2 = bin(self.address.index)[2:]
        num3 = bin(self.address.tag)[2:]
        bitNum = num3 + num2 + num1  # bin을 이용하면 str타입임
        return int(bitNum)  # str -> int

    def getAddr(self):
        return (str(self.address.tag) + str(self.address.index) + str(self.address.offset))
    
    def getData(self, id):
        
        cname = []
        cname.append("법정동코드")
        cname.append("시도명")
        cname.append("시군구명")
        cname.append("법정읍면동명")
        cname.append("산 여부")
        cname.append("지번본번")
        cname.append("지번부번")
        cname.append("도로명코드")
        cname.append("지하여부")
        cname.append("건물본번")
        cname.append("건물부번")
        cname.append("지번일련번호")
        
        print("Data >> %s : %s "%(cname[id],str(self.dt[id])))
        return self.dt[id]

    
# 전체 데이터가 담겨있는 리스트
df = pd.read_table("C:/Users/CJA/Desktop/jibun_seoul.txt",sep='|',encoding='CP949')
df = df.dropna(axis=1)
df = df[:10000]

data_list = []  
for index, row in df.iterrows():
    data1 = []
    tmp = []
    data1.append(row["법정동코드"])
    data1.append(row["시도명"])
    data1.append(row["시군구명"])
    data1.append(row["법정읍면동명"])
    data1.append(row["산 여부"])
    data1.append(row["지번본번"])
    data1.append(row["지번부번"])
    data1.append(row["도로명코드"])
    data1.append(row["지하여부"])
    data1.append(row["건물본번"])
    data1.append(row["건물부번"])
    data1.append(row["지번일련번호"])
    data2 = data(data1)
    tmp.append(data2)
    tmp.append(data2.bit)
    data_list.append(tmp)
    
#data_list = [ [ 데이터 클래스(real data+주소), 2진수로 변환된 주소]]
data_list.sort(key=lambda x:x[1])

## cache data insert

addr1 = data_list[5000]
addr1_data = addr1[0]

idx = 5000

s4 = idx - 2047
b4 = idx + 2048

idx2 = 2047
s3 = idx2 - 127
b3 = idx2 + 128

idx3 = 127
s2 = idx - 7
b2 = idx + 8

idx4 = 7

#L4
for i in range(len(l4)):
    l4[i] = data_list[s4][0].address  # l4에는 데이터의 주소만 넣음
    s4 += 1

#L3    
for i in range(len(l3)):
    id = l4[s3].index
    if (l3[id][0] == -1):  # 첫번째 라인에 들어간 데이터가 없을 때
        l3[id][0] = l4[s3]
    elif (l3[id][0] != -1 and l3[id][1] == -1):  # 첫번째 라인에는 데이터 존재, 두번째 라인은 비어있을 때
        l3[id][1] = l4[s3]
    s3 += 1


find_idx = []

for i in range(len(l3)):
    for x in range(2):
        if(l3[i][x] != -1 and l3[i][x].tag == addr1_data.address.tag):
            find_idx.append(i)
            find_idx.append(x)


#L2
l2 = []

s2 = find_idx[0] - 3
for i in range(0,8):
        l2.append(l3[s2][0])
        l2.append(l3[s2][1])
        s2 += 1
#L1
l1[0] = data_list[5000][0].address


       
    
# hit ratio
def hitratio(input_data, l1, l2, l3, l4):
    hit = 0
    miss = 0
    #L1
    if(l1[0] != 0 and input_data.address.index == l1[0].index and input_data.address.tag == l1[0].tag):
        hit += 1
        print("L1 cache Hit!")
    else:
        miss +=1

    #L2
    if (hit == 0):
        for i in range(16):
            if(l2[i] != -1 and input_data.address.index == l2[i].index and input_data.address.tag == l2[i].tag):
                hit += 1
                print("L2 cache Hit!")
                break
            else:
                miss +=1
                
    #L3
    if (hit == 0):
        for i in range(128):
            if(input_data.address.index == i):
                for n in range(2):
                    if (l3[i][n] != -1 and input_data.address.tag == l3[i][n].tag):
                        hit += 1
                        print("L3 cache Hit!")
                        break
                    else:
                        miss += 1
            else: 
                    miss += 1

    # hit 한 데이터 값 출력
    if(hit == 1):
        for factor in data_list:
                    if(factor[0].bit == addr1_data.address.bit):
                        factor[0].getData(addr1_data.address.offset)
                        break


    # hit ratio
    hit_ratio = hit / (hit+miss)
    print("Hit Ratio : ",hit_ratio*100," %")
    return hit_ratio


hitratio(data_list[5010][0],l1,l2,l3,l4)

# hitratio(data_list[7000][0],l1,l2,l3,l4)
