
<h2> EOS 新节点的加入 <h2>

### **节点最低需求**
软件：系统Ubuntu18.04, 要求EOS nodeos版本不小于1.3.2  
硬件：8G内存，20G可用硬盘

### **启动节点的一般命令**
'''  
./nodeos --data-dir ./data --config-dir ./config --genesis-json ../genesis.json  
'''

- --genesis-json 通常只在第一次启动节点时用于指定所要同步链的一些基本公共信息

- --data-dir指定了链生成数据所要存放的目录

- --config-dir用于指定配置文件所在的目录。第一次启动节点时，可能不存在配置文件，这时启动命令运行会马上失败，但会在你的命令选项指定下的目录生成一个初始的配置文件，这时你就可以根据你的需要配置节点

### **节点config.ini文件的配置**

节点的加入需要在启动EOS时为配置文件配置一些信息，比如生产者名，生产者公钥私钥，还有同步到其它生产者时需要的其它节点IP及端口，上表列出了目前已有链上的一些生产节点，这些信息可以全部或部分的填入到你的nodeos生产节点中的配置文件中。

配置文件config.ini可能存在的路径：
默认路径为： ~/.local/share/eosio/nodeos/config/  
或由客户自己指定路径,启动时加参数 --config-dir ./config/

主要需要配置的字段有以下：

- p2p-listen-endpoint = 0.0.0.0:9876  
此为一般默认配置形式，用于该节点监听同步来自其它节点的连接

- p2p-peer-address = xxx.xxx.xxx.xxx:9876  
此字段可多次配置，用于接收来自其它节点的块同步信息，以下列出一些已存在的生产节点IP  

若需要与dimension出块信息同步，请与dimension技术社群申请获取同步BP IP  
'''  
52.78.XXX.XXX:9876  
13.125.XXX.XXX:9876  
54.180.XXX.XXX:9876  
'''

- producer-name = accountname  
控制此节点的账号名

- signature-provider = public_key=KEY:private_key  
此处需要填入你账号的public_key与private_key字段

- plugin = eosio::chain_api_plugin  
用于使用cleos 控制或获取一些节点信息,此处也可以根据你的需要添加多种额外的plugin