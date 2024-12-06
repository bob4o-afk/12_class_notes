request & response 


трябва да знаят сървъра и клиента за себе си
stateless
не скалира добре

http го имплементира

REST - Representational State Transfer of a resourse
resource based
stateless
client-server based
cacheable
uniform interface


IoT устройствата са - constrain 

coap - constrained application protocol



keep alive - когато имаме връзка с дадено устройство трябва да поддържаме връзката жива

tls - transport layer security

dtls - datagram...



coap message format

version - must be set 01
4 типа собщения:
- confirmable
- non-confirmable
- acknowledgement
- reset - недей да правиш нещо което не си направил

дължина на token-a

code - indicates the request response

message id - 2 byte - match-ваме ack на confirmable suobshteniq

може да имаме proxy което ни пази constrained enviorment-а да не получава много заявки
proxy-то кешира една заявка от http-то и когато се подаде същата заявка се праща от кеша