class SELayer(nn.Module):
    def __init__(self, channel, reduction=16):
        super(SELayer, self).__init__()
        self.avg_pool = nn.AdaptiveAvgPool2d(1)
        self.fc = nn.Sequential(
            nn.Linear(channel, channel // reduction, bias=False),
            nn.ReLU(inplace=True),
            nn.Linear(channel // reduction, channel, bias=False),
            nn.Sigmoid()
        )

    def forward(self, x):
        b, c, _, _ = x.size()
        y = self.avg_pool(x).view(b, c)
        y = self.fc(y).view(b, c, 1, 1)
        return x * y.expand_as(x)

class SEBottleneck(nn.Module):
        expansion = 4

        def __init__(self, inplanes, planes, stride=1, downsample=None, reduction=16):
            super(SEBottleneck, self).__init__()
            self.conv1 = nn.Conv2d(inplanes, planes, kernel_size=1, bias=False)
            self.bn1 = nn.BatchNorm2d(planes)
            self.conv2 = nn.Conv2d(planes, planes, kernel_size=3, stride=stride,
                                   padding=1, bias=False)
            self.bn2 = nn.BatchNorm2d(planes)
            self.conv3 = nn.Conv2d(planes, planes * 4, kernel_size=1, bias=False)
            self.bn3 = nn.BatchNorm2d(planes * 4)
            self.relu = nn.ReLU(inplace=True)
            self.se = SELayer(planes * 4, reduction)
            self.downsample = downsample
            self.stride = stride

        def forward(self, x):
            residual = x

            out = self.conv1(x)
            out = self.bn1(out)
            out = self.relu(out)

            out = self.conv2(out)
            out = self.bn2(out)
            out = self.relu(out)

            out = self.conv3(out)
            out = self.bn3(out)
            out = self.se(out)

            if self.downsample is not None:
                residual = self.downsample(x)

            out += residual
            out = self.relu(out)

            return out

def adjustment_pruningnumber(num_list):
    for index,num in enumerate(num_list):
        if index == 4:
            tmp = int(min(num_list[index],num_list[index-2],num_list[index-4])/3)
            num_list[index] = tmp
            num_list[index-2] = tmp
            num_list[index-4] = tmp
        if index >=5 and index%4 == 0:
            tmp = int(min(num_list[index],num_list[index-2])/2)
            num_list[index] = tmp
            num_list[index-2] = tmp

adjustment_pruningnumber(num_list)