Page({
  data: {
      temp: 27,
      humi: 0,
      light: 50,
      flag_l: false,
      old_flag_l: false,
      temp_flag: false,
      old_temp_flag:false,
      tset:27,   
      hset:50,   
      lset:50,   
  },
  // 事件处理函数
gettoken(){
  var that=this;
  wx.request({//在下面***处填入自己的信息
      url: 'https://iam.cn-north-4.myhuaweicloud.com/v3/auth/tokens',
      data:'{"auth": { "identity": {"methods": ["password"],"password": {"user": {"name": "***","password": "***","domain": {"name": "***"}}}},"scope": {"project": {"name": "cn-north-4"}}}}',
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

triggerStateChange:function(){
  // console.log("开始下发命令。。。");//打印完整消息
  var that=this;  //这个很重要，在下面的回调函数中由于异步问题不能有效修改变量，需要用that获取
  var token = wx.getStorageSync('token');//读缓存中保存的token
  if(that.data.lset > that.data.light){
    wx.request({
      url: 'https://653a151f50.st1.iotda-app.cn-north-4.myhuaweicloud.com:443/v5/iot/661f377e2ccc1a583881a678/devices/661f377e2ccc1a583881a678_yun_dht11/commands',
      data:'{"service_id": "yun","command_name": "led","paras": {"led_flag": true}}',
      method: 'POST', // OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT
      header: {'content-type': 'application/json','X-Auth-Token':token }, //请求的header 
      success: function(res){// success
          // success
          console.log("下发命令成功");//打印完整消息
          //console.log(res);//打印完整消息
      }, 
    });
   console.log("开");//打印完整消息
  }
  else{
    wx.request({
      url: 'https://653a151f50.st1.iotda-app.cn-north-4.myhuaweicloud.com:443/v5/iot/661f377e2ccc1a583881a678/devices/661f377e2ccc1a583881a678_yun_dht11/commands',
      data:'{"service_id": "yun","command_name": "led","paras": {"led_flag": false}}',
      method: 'POST', // OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT
      header: {'content-type': 'application/json','X-Auth-Token':token }, //请求的header 
      success: function(res){// success
          // success
          console.log("下发命令成功");//打印完整消息
          console.log(res);//打印完整消息
      }, 
    });
    console.log("关");//打印完整消息
  }

},

TempChange:function(){
  // console.log("开始下发命令。。。");//打印完整消息
  var that=this;  //这个很重要，在下面的回调函数中由于异步问题不能有效修改变量，需要用that获取
  var token = wx.getStorageSync('token');//读缓存中保存的token
  if(that.data.tset < that.data.temp){
    wx.request({
      url: 'https://653a151f50.st1.iotda-app.cn-north-4.myhuaweicloud.com:443/v5/iot/661f377e2ccc1a583881a678/devices/661f377e2ccc1a583881a678_yun_dht11/commands',
      data:'{"service_id": "yun","command_name": "led","paras": {"temp_flag": true}}',
      method: 'POST', // OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT
      header: {'content-type': 'application/json','X-Auth-Token':token }, //请求的header 
      success: function(res){// success
          // success
          console.log("下发命令成功");//打印完整消息
          //console.log(res);//打印完整消息
      }, 
    });
   console.log("高温");//打印完整消息
  }
  else{
    wx.request({
      url: 'https://653a151f50.st1.iotda-app.cn-north-4.myhuaweicloud.com:443/v5/iot/661f377e2ccc1a583881a678/devices/661f377e2ccc1a583881a678_yun_dht11/commands',
      data:'{"service_id": "yun","command_name": "led","paras": {"temp_flag": false}}',
      method: 'POST', // OPTIONS, GET, HEAD, POST, PUT, DELETE, TRACE, CONNECT
      header: {'content-type': 'application/json','X-Auth-Token':token }, //请求的header 
      success: function(res){// success
          // success
          console.log("下发命令成功");//打印完整消息
          //console.log(res);//打印完整消息
      }, 
    });
    console.log("正常");//打印完整消息
  }

},

lightSet:function(e){
  var that = this
  that.setData({
    lset: e.detail.value
  });
},

tempSet:function(e){
  var that = this
  that.setData({
    tset: e.detail.value
  });
},

check_info(){
  var that = this
  that.setData({
    flag_l: that.data.lset > that.data.light,
    temp_flag: that.data.tset >= that.data.temp
  });
  // console.log(that.data.lset);//打印完整消息
   // 如果状态发生了变化，即上一次开关是开的，现在要关了
  if (that.data.flag_l !== that.data.old_flag_l) {
    that.setData({
      old_flag_l: that.data.flag_l
    });
    that.triggerStateChange();
  }

  if(that.data.temp_flag !== that.data.old_temp_flag){
    that.setData({
      old_temp_flag: that.data.temp_flag
    });
    that.TempChange();
  }
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
    // console.log("获取成功",res)
    that.setData({
      humi:res.data.shadow[0].reported.properties.humidity,
      temp:res.data.shadow[0].reported.properties.temperature,
      light:res.data.shadow[0].reported.properties.light

    })
    // console.log("温度：",that.data.temp);
    }
   });
},

onLoad() {
    var that = this
    setInterval(function(){
      that.gettoken()
      that.getinfo()
      that.check_info()
    }, 500)
    
  },
})
