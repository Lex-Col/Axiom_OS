echo "Timestamp,Temp,Current_uA,Voltage_mV,Capacity" > AXIOM_LOG.csv
while true; do
  TEMP=$(termux-battery-status | grep temperature | awk -F: '{print $2}' | tr -d ', ')
  CURR=$(termux-battery-status | grep current | head -n 1 | awk -F: '{print $2}' | tr -d ', ')
  VOLT=$(termux-battery-status | grep voltage | awk -F: '{print $2}' | tr -d ', ')
  PERC=$(termux-battery-status | grep percentage | awk -F: '{print $2}' | tr -d ', ')
  echo "$(date +%H:%M:%S),$TEMP,$CURR,$VOLT,$PERC" >> AXIOM_LOG.csv
  sleep 10
done
