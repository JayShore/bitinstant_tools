<?php

/* feed the function: 
api method(ex GetQuote), pay_method(ex 
mtgoxcoupon), amount(ex 150), dest_exchange(ex cryptoxchange) 
dest_account(ex //test@test.com), order_id, quote_id (ex 
xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx), and payment_params. 

Note that you only need to supply the needed parameters for each function. 
Function returns an array containing returned parameter titles as keys(ex 
AmountPaidByClientUSD) and contents of the parameter as the value. 

Example: bitinstant_req('GetQuote', 'mtgoxcoupon', 150, 'tradehill', 
'test@test.com') */



function bitinstant_req($api_method, $pay_method, $amount, $dest_exchange, $dest_account, $order_id, $quote_id, $payment_params, $mtgox_code, $mtgox_username) {
//sort your api_method json strings
if($api_method === 'GetQuote') {
$data_string = json_encode(array('pay_method' => $pay_method, 'amount' => $amount, 'dest_exchange' => $dest_exchange, 'dest_account' => $dest_account, 'notify_email' => $dest_account));
}
elseif($api_method === 'CalculateFee') {
$data_string = json_encode(array('pay_method' => $pay_method, 'dest_exchange' => $dest_exchange, 'amount' => $amount));
}
elseif($api_method === 'GetOrderEvents') {
$data_string = json_encode(array('order_id' => $order_id, 'quote_id' => $quote_id));
}
elseif($api_method === 'NewOrder') {
$data_string = json_encode(array('pay_method' => $pay_method, 'quote_id' => $quote_id, 'payment_params' => $payment_params));
}
elseif($api_method === 'GetLimit') {
$data_string = json_encode(array('pay_method' => $pay_method, 'dest_exchange' => $dest_exchange, 'dest_account' => $dest_account));
}
elseif($api_method === 'mtgoxcoupon') {
$data_string = json_encode(array('code' => $mtgox_code, 'mtgoxusername' => $mtgox_username));
}

//start the request
$url = 'https://www.bitinstant.com/api/json/'.$api_method;
$ch = curl_init($url);
curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");                                                                     
curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);                                                                  
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);                                                                      
curl_setopt($ch, CURLOPT_HTTPHEADER, array(                                                                          
    'Content-Type: application/json',                                                                                
    'Content-Length: ' . strlen($data_string))                                                                       
);                                                                                                                   
$output = curl_exec($ch);
curl_close($ch);
return json_decode($output); 
}

//example:
//$request = bitinstant_req('NewOrder', 'mtgoxcoupon', '', 'tradehill', '', '', $quoteid, array("code"=>"$mtgox_code", "mtgoxusername"=>"$mtgox_username"), '', '');

//demo implementation
function instant_to_cryptox($mtgox_code, $amount) {
$request = bitinstant_req('GetQuote', 'mtgoxcoupon', $amount, 'cryptoxchange', 'cryptox_account_number_goes_here');

$quoteid = $request->QuoteID;

$request = bitinstant_req('NewOrder', 'mtgoxcoupon', '', 'cryptoxchange', '', '', $quoteid, array("code"=>"$mtgox_code", "mtgoxusername"=>"mtgox_username_goes_here"), '', '');
return $request->OrderID;
}



?>