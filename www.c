#!/bin/sh
# cat /etc/crontabs/root
#*/5 * * * * sh /root/aatuo_wgc   wg1.wgaliszvp.
#   auto_wgc wg1.wgaliszvp.
#   iproute_for_wgaliszvp







ccdns() {
iface=$1
if echo $iface |grep wg50
then
	echo wg50 go to check dns case

	startTime="1300"
	endTime="1800"
	currentTime=`date +"%M%S"`
	if [[ $currentTime -ge $startTime && $currentTime -le $endTime ]];  
	then
		echo dnsmasq for $iface `date` >>/tmp/dnsmasq_tmp_$iface
		/etc/init.d/dnsmasq restart

	fi

	startTime="4300"
	endTime="4800"
	currentTime=`date +"%M%S"`
	if [[ $currentTime -ge $startTime && $currentTime -le $endTime ]];  
	then
		echo dnsmasq for $iface `date` >>/tmp/dnsmasq_tmp_$iface
		/etc/init.d/dnsmasq restart

	fi

	startTime="184300"
	endTime="184800"
	currentTime=`date +"%H%M%S"`
	if [[ $currentTime -ge $startTime && $currentTime -le $endTime ]];  
	then
		date > /tmp/dnsmasq_tmp_$iface
	fi


fi

}






st() {
d1=$1
echo $d1 | awk -F '[.]' '{print $1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19}' >  /tmp/wg_tmp_check_0001

for iii in `cat /tmp/wg_tmp_check_0001`
do


iface=$iii

wg |grep $iface || (sh /root/$iface ; sleep 7 ; echo $iface --- `date`>>/tmp/boot_wg_start_log )

#iface=wgaliszvp
last_handshake=`wg show ${iface} latest-handshakes | awk '{print $2}'`

if [ $last_handshake -eq 0 ]
then
	ccdns $iface
	sh /root/$iface
fi

if [ $last_handshake -gt 0 ]
then
idle_seconds=$((`date +%s`-${last_handshake}))
echo $idle_seconds
		

		if [ $idle_seconds -gt 300 ]
		then
			ccdns $iface
			sh /root/$iface
		fi
fi
done



}

st $1
exit 0;
