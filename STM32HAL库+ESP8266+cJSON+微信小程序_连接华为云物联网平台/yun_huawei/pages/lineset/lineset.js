//引入echarts文件
import * as echarts from '../../ec-canvas/echarts';

function line_set(chart,time_data,hum_data,tem_data,ligh_data) {
  var option = {
    animation: false,
    title: {
      text: '实时环境数据',
      left: 'center'
    },
    tooltip: {
      trigger: 'axis'
    },
    legend: {
      data: ['温度', '湿度', '光照'],
       top: 30,
    },
    grid: {
      left: '3%',
      right: '6%',
      bottom: '3%',
      containLabel: true
    },
    toolbox: {
      feature: {
        saveAsImage: {}
      }
    },
    xAxis: {
      type: 'category',
      boundaryGap: false,
      data: time_data,
      nameGap: -1,
      axisLabel: {
        fontSize: 10
      }
    },
    yAxis: {
      type: 'value',
      axisLabel: {
        fontSize: 10
      }
    },
    series: [
      {
        name: '温度',
        type: 'line',
        stack: 'Total1',
        data: tem_data
      },
      {
        name: '湿度',
        type: 'line',
        stack: 'Total2',
        data: hum_data
      },
      {
        name: '光照',
        type: 'line',
        stack: 'Total3',
        data: ligh_data
      }
    ]
  };
  chart.setOption(option);
}

Page({
  /**
   * 页面的初始数据
   */
  data: {
    ec: {
    },
    Temperature: [],
    Humidity: [],
    Light: [],
    Time: []
  },

//初始化第一个图表
init_chart: function (time_data,hum_data,tem_data,ligh_data) {        
    this.oneComponent.init((canvas, width, height, dpr) => {
        const chart = echarts.init(canvas, null, {
            width: width,
            height: height,
            devicePixelRatio: dpr 
        });
        line_set(chart,time_data,hum_data,tem_data,ligh_data)
        this.chart = chart;
        return chart;
    });
},

gettoken(){
  var that =this;  //这个很重要，在下面的回调函数中由于异步问题不能有效修改变量，需要用that获取
  wx.request({
      url: 'https://iam.cn-north-4.myhuaweicloud.com/v3/auth/tokens',
      data:'{"auth": { "identity": {"methods": ["password"],"password": {"user": {"name": "yuanhao","password": "1425724354zz","domain": {"name": "hid_duoaif5vulv-g8i"}}}},"scope": {"project": {"name": "cn-north-4"}}}}',
      method: 'POST', // OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT
      header: {'content-type': 'application/json' }, // 请求的 header 
      success: function(res){// success
        // success
          var token='';
          token=JSON.stringify(res.header['X-Subject-Token']);//解析消息头的token
          token=token.replaceAll("\"", "");
          wx.setStorageSync('token',token);
          //console.log("获取token=\n"+token);//打印token
      },
  });
},
getinfo(){
  var that = this
  var token = wx.getStorageSync('token');//读缓存中保存的token
    wx.request({
      url: 'https://653a151f50.st1.iotda-app.cn-north-4.myhuaweicloud.com:443/v5/iot/661f377e2ccc1a583881a678/devices/661f377e2ccc1a583881a678_yun_dht11/shadow',
      data:'',
      method: 'GET', // OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT
      header: {'content-type': 'application/json','X-Auth-Token':token }, //请求的header 
    
    success: function (res) {
    var temp=[];
    var humi=[];
    var ligh=[];
    var date=[];

    const now = new Date();
    // 格式化时间
    const hours = now.getHours().toString().padStart(2, '0');
    const minutes = now.getMinutes().toString().padStart(2, '0');
    const seconds = now.getSeconds().toString().padStart(2, '0');
    const formattedTime = `${hours}:${minutes}:${seconds}`;

    temp = that.data.Temperature;
    humi = that.data.Humidity;
    ligh = that.data.Light;
    date = that.data.Time;
    temp.push(res.data.shadow[0].reported.properties.temperature);
    humi.push(res.data.shadow[0].reported.properties.humidity);
    ligh.push(res.data.shadow[0].reported.properties.light);
    date.push(formattedTime);
    if (temp.length > 7) {
      temp.shift(); // 移除数组的第一个元素
      humi.shift();
      ligh.shift();
      date.shift();
    }
    //console.log("获取成功",ligh)
    that.setData({
      Temperature:temp,
      Humidity:humi,
      Light:ligh,
      Time:date
    })
     that.init_chart(date,humi,temp,ligh) 
    }
   });
},
/**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    var that = this;
    that.oneComponent = that.selectComponent('#myechart');
    that.getinfo()
    that.setData({                    //每隔5s刷新一次
      timer: setInterval(function () {
        that.getinfo();
    }, 1500)
    })
  }
})

