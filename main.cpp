#include <QApplication>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QDebug>

#include <math.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef HELLOHANDLE_H
#define HELLOHANDLE_H

/*
   Mathieu Stefani, 07 février 2016

   Example of a REST endpoint with routing
*/

#include <algorithm>

#include "pistache/mailbox.h"
#include "pistache/prototype.h"
#include "pistache/flags.h"
#include "pistache/typeid.h"
#include "pistache/serializer/rapidjson.h"
#include "pistache/net.h"
#include "pistache/stream.h"
#include "pistache/peer.h"
#include "pistache/reactor.h"
#include "pistache/description.h"
#include "pistache/cookie.h"
#include "pistache/http_defs.h"
#include "pistache/http.h"
#include "pistache/http_header.h"
#include "pistache/async.h"
#include "pistache/timer_pool.h"
#include "pistache/os.h"
#include "pistache/iterator_adapter.h"
#include "pistache/client.h"
#include "pistache/view.h"
#include "pistache/common.h"
#include "pistache/transport.h"
#include "pistache/optional.h"
#include "pistache/mime.h"
#include "pistache/router.h"
#include "pistache/listener.h"

#include "pistache/endpoint.h"
#include "pistache/tcp.h"


#include <iostream>
#include <cstdlib>
#include <sstream>
#include <memory>

#include "./ProofKits/include/HashHelper.h"
#include "./ProofKits/include/ProofKitPair.h"
#include "./ProofKits/include/Proof.h"
#include "./ProofKits/include/RangeProof.h"
#include "./ProofKits/include/Prover.h"

QJsonObject ObjectFromString(const QString& in);

QJsonObject recursiveJSONobj(QJsonObject obj);
QJsonArray recursiveJSONarray(QJsonArray arr);


using namespace std;
using namespace Pistache;
using namespace Http;

void printCookies(const Http::Request& req) {
	auto cookies = req.cookies();
	std::cout << "Cookies: [" << std::endl;
	const std::string indent(4, ' ');
	for (const auto& c: cookies) {
		std::cout << indent << c.name << " = " << c.value << std::endl;
	}
	std::cout << "]" << std::endl;
}

QJsonObject proofkitGen(unsigned int value)
{
	RangeProof rangeProof(value);

	std::stringstream buffer;
	QJsonObject myObj = QJsonObject();
	
	myObj.insert("lowerProofKit", QJsonValue(QString::fromStdString(rangeProof.getLowerProofKit().getProofKit() )));
	myObj.insert("upperProofKit", QJsonValue(QString::fromStdString(rangeProof.getUpperProofKit().getProofKit()  )));
	myObj.insert("secret", QJsonValue(QString::fromStdString(rangeProof.getSecretKey1().getKey() )));
	
	//~ buffer << "{"
		//~ << "\"lowerProofKit\": \"" << rangeProof.getLowerProofKit().getProofKit() << "\","
		//~ << "\"upperProofKit\": \"" << rangeProof.getUpperProofKit().getProofKit() << "\""
		//~ << "\"secret\": \"" << rangeProof.getSecretKey1().getKey() << "\""
		//~ << "}" << std::endl;

	//~ return buffer.str();
	
	return myObj;

}


namespace Generic {

#define JASON "{\"transactions\":[{\"id\":\"652cedbe-ceb4-4c73-9c33-924c69629c28\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"0gGaE5xZPDWaLhU0Tz3CFEnCEyRKFLZqv0dhbOBwcUY\",\"holder\":{\"name\":\"\",\"is_alias\":false},\"bank_routing\":{\"scheme\":\"bb.03.nl.nl\",\"address\":\"OBP\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"470af7b8-0836-4cde-8f74-9c635f130fb4\"}},\"details\":{\"type\":\"SANDBOX_TAN\",\"description\":\"Small Beer\",\"posted\":\"2018-05-31T08:54:03Z\",\"completed\":\"2018-05-31T08:54:03Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15848.09\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-21.00\"}}},{\"id\":\"5d005894-3a18-408c-a949-fd10dbe75539\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"0gGaE5xZPDWaLhU0Tz3CFEnCEyRKFLZqv0dhbOBwcUY\",\"holder\":{\"name\":\"\",\"is_alias\":false},\"bank_routing\":{\"scheme\":\"bb.03.nl.nl\",\"address\":\"OBP\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"470af7b8-0836-4cde-8f74-9c635f130fb4\"}},\"details\":{\"type\":\"SANDBOX_TAN\",\"description\":\"Small Beer\",\"posted\":\"2018-05-31T08:52:33Z\",\"completed\":\"2018-05-31T08:52:33Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15869.09\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-21.00\"}}},{\"id\":\"aac3e423-3264-41fe-8833-664b28d2ae08\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"tNGaeMDgfQcUZK_jZH12RIsFidIAoPYrsKDp9DpEDtE\",\"holder\":{\"name\":\"Salary\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Betaal Ref 89416\",\"posted\":\"2017-12-30T21:17:05Z\",\"completed\":\"2017-12-30T21:17:05Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15890.09\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"1486.98\"}}},{\"id\":\"04f3fdd3-b3d6-4dba-bdeb-ce915748b5c0\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"5grUpJtjoWD83NvDfDCXa1sIjMbgJWSfNppVQyD6k1U\",\"holder\":{\"name\":\"Post nl\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"spaargeld\",\"posted\":\"2017-12-30T07:57:07Z\",\"completed\":\"2017-12-30T07:57:07Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14403.11\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-345.87\"}}},{\"id\":\"0adb8660-02fc-4eab-a7ee-606955465eec\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"gXMbkHTS37sAg5lhhhZ5UIF0_c2EgBnHuZ2NUeOSb9k\",\"holder\":{\"name\":\"Tele2\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"BT\",\"posted\":\"2017-12-29T09:09:30Z\",\"completed\":\"2017-12-29T09:09:30Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14748.98\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-24.80\"}}},{\"id\":\"567bf880-506d-47c3-b9f9-314cc4aad416\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"EJz9UA_se58uS-ncui3g9hOeAwkwRNua7V9jonfxoKM\",\"holder\":{\"name\":\"Albert Heijn\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-12-16T11:57:22Z\",\"completed\":\"2017-12-16T11:57:22Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14773.78\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-70.90\"}}},{\"id\":\"fb91b270-0c88-4b0f-a987-221f3b758572\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"y1p0ONkkDjseqAB4IRky9xFIvGjscmyUktXrpd1lt1Q\",\"holder\":{\"name\":\"Coffee Shop Ibiza\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Koffie\",\"posted\":\"2017-12-12T05:17:45Z\",\"completed\":\"2017-12-12T05:17:45Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14844.68\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-5.46\"}}},{\"id\":\"2fcceb51-00f3-4c8b-bbc3-923eba39555f\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"sXJEDtSkRdepeFHj5B9Fn2sQNKo9kkKIHutjTqizdic\",\"holder\":{\"name\":\"Bakers and Roasters\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"restaurants\",\"posted\":\"2017-12-12T05:14:47Z\",\"completed\":\"2017-12-12T05:14:47Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14850.14\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-31.36\"}}},{\"id\":\"c50705a2-7525-4b20-b5d2-7f7e9bf97f5c\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"6JQ5ms-7yLN7j0jjeiQMwG1tHshxcjJ2AkwRBLqXjAU\",\"holder\":{\"name\":\"Bridges\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"restaurants\",\"posted\":\"2017-12-11T22:42:17Z\",\"completed\":\"2017-12-11T22:42:17Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14881.50\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-70.33\"}}},{\"id\":\"ab7c237e-cbeb-4a38-baa1-5d60b774772a\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"stksYmECwz2KuyAHd-FRqi_AdACYtImSZEITqqAFiDk\",\"holder\":{\"name\":\"Hutspot\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-12-11T19:06:21Z\",\"completed\":\"2017-12-11T19:06:21Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14951.83\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-38.82\"}}},{\"id\":\"a50db3ed-a10e-483e-95bf-0fb2d7775d41\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"RN4Q7VSOE9muWDZuxJ4_UiBpklmRtqNKVX5zOhel6Bg\",\"holder\":{\"name\":\"Dept\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-12-11T03:22:14Z\",\"completed\":\"2017-12-11T03:22:14Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14990.65\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-76.34\"}}},{\"id\":\"9c7f97cb-6fb9-4280-904b-dfafdb24dcb3\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"EJz9UA_se58uS-ncui3g9hOeAwkwRNua7V9jonfxoKM\",\"holder\":{\"name\":\"Albert Heijn\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-12-04T20:28:04Z\",\"completed\":\"2017-12-04T20:28:04Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15066.99\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-51.22\"}}},{\"id\":\"48e4abbe-483a-4efe-934f-3e089cf4f8ca\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"f7QCod7kQBjaVwqI3ZA1xqJGb91gBfYP8UI5eBszxmI\",\"holder\":{\"name\":\"Shell Filling Station\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Benzinepomp\",\"posted\":\"2017-12-04T10:30:21Z\",\"completed\":\"2017-12-04T10:30:21Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15118.21\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-67.18\"}}},{\"id\":\"60109347-4bcd-4e41-92f5-2b6db66593ea\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"nJPQwv0MKaDenVgioY6dlZsoKMQB1g5ov-p97Z4N_mI\",\"holder\":{\"name\":\"Vewin\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Water\",\"posted\":\"2017-12-01T23:20:32Z\",\"completed\":\"2017-12-01T23:20:32Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15185.39\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-27.15\"}}},{\"id\":\"1fe51d85-39c3-4de9-971f-fd8035fa85db\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"HkRJDMV0WYHE6Vy54fJMEdd0F_L4OjZXpmDppdTcAAM\",\"holder\":{\"name\":\"Belastingdienst\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Belastingnummer 4583245\",\"posted\":\"2017-12-01T18:54:14Z\",\"completed\":\"2017-12-01T18:54:14Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15212.54\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-27.15\"}}},{\"id\":\"4cd081d6-3618-4d37-a8cf-b2eeebd7d6cf\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"PKXTQ82reeOgv3aFH6sW_SieSg-oDuKMS6rszO3Xa9w\",\"holder\":{\"name\":\"nuon\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Gas / Elec\",\"posted\":\"2017-12-01T01:55:42Z\",\"completed\":\"2017-12-01T01:55:42Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15239.69\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-100.80\"}}},{\"id\":\"4f54e62f-4f27-42fd-8769-b2b8511d1b54\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"BPXFI5zS0PDsmPtNZpbc0osGJ1oo8ayGW-FmG40Dgjc\",\"holder\":{\"name\":\"Golf Club Anderstein\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Maandelijks golflidmaatschap\",\"posted\":\"2017-12-01T01:22:55Z\",\"completed\":\"2017-12-01T01:22:55Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15340.49\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-34.59\"}}},{\"id\":\"724d420a-a26b-45a7-a268-0856b0663339\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"5grUpJtjoWD83NvDfDCXa1sIjMbgJWSfNppVQyD6k1U\",\"holder\":{\"name\":\"Post nl\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"spaargeld\",\"posted\":\"2017-11-30T09:25:44Z\",\"completed\":\"2017-11-30T09:25:44Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15375.08\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-345.87\"}}},{\"id\":\"3869be40-92c8-4317-8bd4-6e12d8ed3b66\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"tNGaeMDgfQcUZK_jZH12RIsFidIAoPYrsKDp9DpEDtE\",\"holder\":{\"name\":\"Salary\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Betaal Ref 66412\",\"posted\":\"2017-11-30T09:06:00Z\",\"completed\":\"2017-11-30T09:06:00Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15720.95\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"1486.98\"}}},{\"id\":\"152ee809-8419-4328-be89-1ead6d2178d5\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"gXMbkHTS37sAg5lhhhZ5UIF0_c2EgBnHuZ2NUeOSb9k\",\"holder\":{\"name\":\"Tele2\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"BT\",\"posted\":\"2017-11-15T23:11:49Z\",\"completed\":\"2017-11-15T23:11:49Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14233.97\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-24.80\"}}},{\"id\":\"a957981e-8b49-4705-b3ee-e6727d311b39\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"EJz9UA_se58uS-ncui3g9hOeAwkwRNua7V9jonfxoKM\",\"holder\":{\"name\":\"Albert Heijn\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-11-14T09:07:50Z\",\"completed\":\"2017-11-14T09:07:50Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14258.77\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-53.18\"}}},{\"id\":\"da329cf9-c111-4942-961b-7a6c50af0dbc\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"f7QCod7kQBjaVwqI3ZA1xqJGb91gBfYP8UI5eBszxmI\",\"holder\":{\"name\":\"Shell Filling Station\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Benzinepomp\",\"posted\":\"2017-11-14T08:10:18Z\",\"completed\":\"2017-11-14T08:10:18Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14311.95\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-72.52\"}}},{\"id\":\"539cb5c7-a80f-4197-9fb6-e677cdfc35ba\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"_wpe4ybGN-Wr750WOZiqbatZD-CqlTAhwaQWREpWTeg\",\"holder\":{\"name\":\"Midtown Grill\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"restaurants\",\"posted\":\"2017-11-13T20:11:57Z\",\"completed\":\"2017-11-13T20:11:57Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14384.47\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-34.69\"}}},{\"id\":\"3b8b8518-e1df-4b1f-a4e9-7de48a863078\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"myy5f1wWFHLBj2zVlSmIOwewEBZRev7LGP3a4ThUCAM\",\"holder\":{\"name\":\"Belushis\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Bar\",\"posted\":\"2017-11-13T12:58:13Z\",\"completed\":\"2017-11-13T12:58:13Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14419.16\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-22.87\"}}},{\"id\":\"e0726aad-deb6-48ab-bbae-885499e726ff\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"y1p0ONkkDjseqAB4IRky9xFIvGjscmyUktXrpd1lt1Q\",\"holder\":{\"name\":\"Coffee Shop Ibiza\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Koffie\",\"posted\":\"2017-11-13T09:42:04Z\",\"completed\":\"2017-11-13T09:42:04Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14442.03\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-6.35\"}}},{\"id\":\"eccd0d4b-606d-4c30-9672-344463f49618\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"y1p0ONkkDjseqAB4IRky9xFIvGjscmyUktXrpd1lt1Q\",\"holder\":{\"name\":\"Coffee Shop Ibiza\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Koffie\",\"posted\":\"2017-11-09T11:17:15Z\",\"completed\":\"2017-11-09T11:17:15Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14448.38\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-13.26\"}}},{\"id\":\"7c425790-f376-4253-881d-12fed255e988\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"EJz9UA_se58uS-ncui3g9hOeAwkwRNua7V9jonfxoKM\",\"holder\":{\"name\":\"Albert Heijn\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-11-09T09:03:02Z\",\"completed\":\"2017-11-09T09:03:02Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14461.64\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-32.86\"}}},{\"id\":\"9ab61f22-e001-41c3-ae54-0afe3feb0ab9\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"jXLC09kWQuxW6lRcQYHHv6eJcat84eRaIF4WR4roDTU\",\"holder\":{\"name\":\"Daalder Amsterdam\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"restaurants\",\"posted\":\"2017-11-07T09:23:56Z\",\"completed\":\"2017-11-07T09:23:56Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14494.50\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-85.05\"}}},{\"id\":\"81894290-bf47-4340-88ff-665caf163e84\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"stksYmECwz2KuyAHd-FRqi_AdACYtImSZEITqqAFiDk\",\"holder\":{\"name\":\"Hutspot\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-11-07T00:50:36Z\",\"completed\":\"2017-11-07T00:50:36Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14579.55\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-34.69\"}}},{\"id\":\"02dcf962-2903-4f30-ad60-aab572c29b07\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"zCMUmHhxWNOl-PF9IbkZzmK7EAObrDrUeXG5cn_1b-M\",\"holder\":{\"name\":\"de Dijenkorf\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-11-06T23:29:44Z\",\"completed\":\"2017-11-06T23:29:44Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14614.24\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-93.44\"}}},{\"id\":\"9e233f63-b164-4f0a-ac3b-8a8b59be2b1e\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"7qoZIJM-7lLNVkrYuzRYQRliq9FWEneagORCPylAonQ\",\"holder\":{\"name\":\"L I K E S T A T I O N E R Y\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-11-04T14:17:49Z\",\"completed\":\"2017-11-04T14:17:49Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14707.68\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-6.35\"}}},{\"id\":\"f78b319c-def0-4a8d-a2f8-d20ee8596c29\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"gh3A2PXJN0PeQKgLnJ4652mgqFLE96FG-8VTRpcCXBA\",\"holder\":{\"name\":\"Credit Card Visa\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-11-04T03:15:35Z\",\"completed\":\"2017-11-04T03:15:35Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14714.03\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-72.52\"}}},{\"id\":\"3144a685-74cf-485b-ad53-1b4efe15515e\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"HkRJDMV0WYHE6Vy54fJMEdd0F_L4OjZXpmDppdTcAAM\",\"holder\":{\"name\":\"Belastingdienst\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Gemeentebelastingen\",\"posted\":\"2017-11-02T20:10:35Z\",\"completed\":\"2017-11-02T20:10:35Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14786.55\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-27.15\"}}},{\"id\":\"64da8d5d-4347-4718-acc1-4bd1bba278e2\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"BPXFI5zS0PDsmPtNZpbc0osGJ1oo8ayGW-FmG40Dgjc\",\"holder\":{\"name\":\"Golf Club Anderstein\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Maandelijks golflidmaatschap\",\"posted\":\"2017-11-02T17:28:25Z\",\"completed\":\"2017-11-02T17:28:25Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14813.70\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-34.59\"}}},{\"id\":\"1fa05c58-8af8-4d26-9f17-1a83dec2246e\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"PKXTQ82reeOgv3aFH6sW_SieSg-oDuKMS6rszO3Xa9w\",\"holder\":{\"name\":\"nuon\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Gas / Elec\",\"posted\":\"2017-11-02T08:10:02Z\",\"completed\":\"2017-11-02T08:10:02Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14848.29\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-100.80\"}}},{\"id\":\"42552b1b-4f2a-493a-bd22-001a029f0cf1\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"nJPQwv0MKaDenVgioY6dlZsoKMQB1g5ov-p97Z4N_mI\",\"holder\":{\"name\":\"Vewin\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Water\",\"posted\":\"2017-11-02T02:58:52Z\",\"completed\":\"2017-11-02T02:58:52Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14949.09\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-27.15\"}}},{\"id\":\"55faa22f-6176-422f-9b2e-627596c0b975\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"5grUpJtjoWD83NvDfDCXa1sIjMbgJWSfNppVQyD6k1U\",\"holder\":{\"name\":\"Post nl\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"spaargeld\",\"posted\":\"2017-10-30T04:25:29Z\",\"completed\":\"2017-10-30T04:25:29Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14976.24\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-345.87\"}}},{\"id\":\"38560bab-baa5-436d-8650-6a719ed07efe\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"tNGaeMDgfQcUZK_jZH12RIsFidIAoPYrsKDp9DpEDtE\",\"holder\":{\"name\":\"Salary\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Betaal Ref 56412\",\"posted\":\"2017-10-29T05:23:46Z\",\"completed\":\"2017-10-29T05:23:46Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"15322.11\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"1486.98\"}}},{\"id\":\"b9632986-7d07-4783-a666-b77cacc3e1ec\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"gXMbkHTS37sAg5lhhhZ5UIF0_c2EgBnHuZ2NUeOSb9k\",\"holder\":{\"name\":\"Tele2\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"BT\",\"posted\":\"2017-10-20T16:08:27Z\",\"completed\":\"2017-10-20T16:08:27Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"13835.13\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-24.80\"}}},{\"id\":\"50299d7e-8c70-450f-989c-8f74f911a856\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"f7QCod7kQBjaVwqI3ZA1xqJGb91gBfYP8UI5eBszxmI\",\"holder\":{\"name\":\"Shell Filling Station\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Benzinepomp\",\"posted\":\"2017-10-12T15:26:11Z\",\"completed\":\"2017-10-12T15:26:11Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"13859.93\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-72.52\"}}},{\"id\":\"79be8627-17e8-4d2a-a33f-af246a679953\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"myy5f1wWFHLBj2zVlSmIOwewEBZRev7LGP3a4ThUCAM\",\"holder\":{\"name\":\"Belushis\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Bar\",\"posted\":\"2017-10-12T06:44:30Z\",\"completed\":\"2017-10-12T06:44:30Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"13932.45\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-43.74\"}}},{\"id\":\"a8a0ba9e-60eb-4943-bad9-b5676b673f30\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"EJz9UA_se58uS-ncui3g9hOeAwkwRNua7V9jonfxoKM\",\"holder\":{\"name\":\"Albert Heijn\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-10-11T21:44:40Z\",\"completed\":\"2017-10-11T21:44:40Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"13976.19\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-78.30\"}}},{\"id\":\"694e4857-502a-4d7d-aaf4-1ed7b5c168df\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"_wpe4ybGN-Wr750WOZiqbatZD-CqlTAhwaQWREpWTeg\",\"holder\":{\"name\":\"Midtown Grill\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"restaurants\",\"posted\":\"2017-10-09T07:37:06Z\",\"completed\":\"2017-10-09T07:37:06Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14054.49\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-88.46\"}}},{\"id\":\"5cd61a45-5df7-4bbd-9252-249538c1adef\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"y1p0ONkkDjseqAB4IRky9xFIvGjscmyUktXrpd1lt1Q\",\"holder\":{\"name\":\"Coffee Shop Ibiza\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Koffie\",\"posted\":\"2017-10-05T17:33:12Z\",\"completed\":\"2017-10-05T17:33:12Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14142.95\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-13.26\"}}},{\"id\":\"1628689f-266b-4030-8270-e1465fdead86\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"OqLRNS2S_YLqcQFYlHrZ5i60pGOuOUw3Mrp3uKXxI0A\",\"holder\":{\"name\":\"Q-Park\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"parkeren\",\"posted\":\"2017-10-05T10:27:30Z\",\"completed\":\"2017-10-05T10:27:30Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14156.21\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-5.41\"}}},{\"id\":\"ce9bf247-2f94-4341-98fa-5fdd268b89a7\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"_wpe4ybGN-Wr750WOZiqbatZD-CqlTAhwaQWREpWTeg\",\"holder\":{\"name\":\"Midtown Grill\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"restaurants\",\"posted\":\"2017-10-05T05:40:08Z\",\"completed\":\"2017-10-05T05:40:08Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14161.62\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-42.63\"}}},{\"id\":\"b0b48a77-89ea-4351-b15f-d47fa483600e\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"y1p0ONkkDjseqAB4IRky9xFIvGjscmyUktXrpd1lt1Q\",\"holder\":{\"name\":\"Coffee Shop Ibiza\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Koffie\",\"posted\":\"2017-10-05T04:34:49Z\",\"completed\":\"2017-10-05T04:34:49Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14204.25\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-6.35\"}}},{\"id\":\"16186a77-8821-4bdf-bc1f-1ba8aa9ab6a9\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"bWVx7UN-0Re-JsuQgA2QXU_3zyU7l5-GOoVkOuwoMbM\",\"holder\":{\"name\":\"Dagwinkel\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Boodschappen doen\",\"posted\":\"2017-10-05T03:47:13Z\",\"completed\":\"2017-10-05T03:47:13Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14210.60\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-54.67\"}}},{\"id\":\"b67c6c06-604d-4d94-b805-feee58cdff23\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"Ts4MK0p6OMn5Z-YMT3zfxb6zpXIalWlJEGHJQlTvMok\",\"holder\":{\"name\":\"Ivy\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Bloemist\",\"posted\":\"2017-10-05T03:25:04Z\",\"completed\":\"2017-10-05T03:25:04Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14265.27\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-27.15\"}}},{\"id\":\"acba66e8-1e3f-4dfe-9354-fbd9dfce4522\",\"this_account\":{\"id\":\"d935cf14-e619-4d9e-af90-f343539f80ca\",\"bank_routing\":{\"scheme\":\"OBP\",\"address\":\"bb.03.nl.nl\"},\"account_routing\":{\"scheme\":\"OBP\",\"address\":\"d935cf14-e619-4d9e-af90-f343539f80ca\"},\"holders\":[{\"name\":\"Robert.Nl.03\",\"is_alias\":false}]},\"other_account\":{\"id\":\"f7QCod7kQBjaVwqI3ZA1xqJGb91gBfYP8UI5eBszxmI\",\"holder\":{\"name\":\"Shell Filling Station\",\"is_alias\":false},\"bank_routing\":{\"scheme\":null,\"address\":null},\"account_routing\":{\"scheme\":null,\"address\":null}},\"details\":{\"type\":\"10219\",\"description\":\"Benzinepomp\",\"posted\":\"2017-10-05T01:33:52Z\",\"completed\":\"2017-10-05T01:33:52Z\",\"new_balance\":{\"currency\":\"EUR\",\"amount\":\"14292.42\"},\"value\":{\"currency\":\"EUR\",\"amount\":\"-72.52\"}}}]}"

}

class StatsEndpoint {
public:
	StatsEndpoint(Address addr)
		: httpEndpoint(std::make_shared<Http::Endpoint>(addr))
	{ }

	void init(size_t thr = 2) {
		auto opts = Http::Endpoint::options()
			.threads(thr)
			.flags(Tcp::Options::InstallSignalHandler | Tcp::Options::ReuseAddr);
		httpEndpoint->init(opts);
		setupRoutes();
	}

	void start() {
		httpEndpoint->setHandler(router.handler());
		httpEndpoint->serve();
	}

	void shutdown() {
		httpEndpoint->shutdown();
	}

private:
	void setupRoutes() {
		using namespace Rest;

		Routes::Post(router, "/record/:name/:value?", Routes::bind(&StatsEndpoint::doRecordMetric, this));
		Routes::Get(router, "/value/:name", Routes::bind(&StatsEndpoint::doGetMetric, this));
		Routes::Get(router, "/transactionzkp/:transactno", Routes::bind(&StatsEndpoint::handleReady, this));
		Routes::Get(router, "/auth", Routes::bind(&StatsEndpoint::doAuth, this));

	}


	void handleReady(const Rest::Request& request, Http::ResponseWriter response)
	{
		auto name = request.param(":transactno").as<std::string>();
		
		int lel = std::stoi(name);
		
		QNetworkAccessManager *mgr = new QNetworkAccessManager();


		QNetworkRequest myReq = QNetworkRequest(QUrl(QString("https://beyondbanking.openbankproject.com/obp/v3.0.0/my/banks/bb.03.nl.nl/accounts/d935cf14-e619-4d9e-af90-f343539f80ca/transactions")));

		myReq.setRawHeader("Content-Type", "application/json");
		myReq.setRawHeader("Authorization", "DirectLogin token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyIiOiIifQ.54JPGFR9fDJ6tk68NW59qsSMtsQXQNezu_5Tc1O601k");

		QNetworkReply * hahah = mgr->get(myReq);

		QEventLoop eventLoop;
		// also dispose the event loop after the reply has arrived
		QObject::connect(mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
		eventLoop.exec();


		QString tehJason =  QString::fromStdString(hahah->readAll().toStdString());

		QJsonObject blep = ObjectFromString(tehJason);

		QJsonValue transactionArrayVal = blep.take("transactions");

		qDebug() << transactionArrayVal.isArray();

		QJsonArray transactionArray = transactionArrayVal.toArray();
		
		QJsonArray jsonArray = QJsonArray();
		
		jsonArray.append(transactionArray.at(lel));

		QJsonDocument doc;
		doc.setObject(recursiveJSONarray(jsonArray).at(0).toObject());
		QString dataToString(doc.toJson());

		std::string utf8_text = dataToString.toUtf8().constData();


		response.headers().add<Header::ContentType>(MIME(Application, Json));
		response.send(Http::Code::Ok, utf8_text);
		//~ proofkitGen(lel);
		//~ response.send(Http::Code::Ok, );
	}

	void doRecordMetric(const Rest::Request& request, Http::ResponseWriter response) {
		auto name = request.param(":name").as<std::string>();

		Guard guard(metricsLock);
		auto it = std::find_if(metrics.begin(), metrics.end(), [&](const Metric& metric) {
			return metric.name() == name;
		});

		int val = 1;
		if (request.hasParam(":value")) {
			auto value = request.param(":value");
			val = value.as<int>();
		}

		if (it == std::end(metrics)) {
			metrics.push_back(Metric(std::move(name), val));
			response.send(Http::Code::Created, std::to_string(val));
		}
		else {
			auto &metric = *it;
			metric.incr(val);
			response.send(Http::Code::Ok, std::to_string(metric.value()));
		}

	}

	void doGetMetric(const Rest::Request& request, Http::ResponseWriter response) {
		auto name = request.param(":name").as<std::string>();

		Guard guard(metricsLock);
		auto it = std::find_if(metrics.begin(), metrics.end(), [&](const Metric& metric) {
			return metric.name() == name;
		});

		if (it == std::end(metrics)) {
			response.send(Http::Code::Not_Found, "Metric does not exist");
		} else {
			const auto& metric = *it;
			response.send(Http::Code::Ok, std::to_string(metric.value()));
		}

	}

	void doAuth(const Rest::Request& request, Http::ResponseWriter response) {
		printCookies(request);
		response.cookies()
			.add(Http::Cookie("lang", "en-US"));
		response.send(Http::Code::Ok);
	}

	class Metric {
	public:
		Metric(std::string name, int initialValue = 1)
			: name_(std::move(name))
			, value_(initialValue)
		{ }

		int incr(int n = 1) {
			int old = value_;
			value_ += n;
			return old;
		}

		int value() const {
			return value_;
		}

		std::string name() const {
			return name_;
		}
	private:
		std::string name_;
		int value_;
	};

	typedef std::mutex Lock;
	typedef std::lock_guard<Lock> Guard;
	Lock metricsLock;
	std::vector<Metric> metrics;

	std::shared_ptr<Http::Endpoint> httpEndpoint;
	Rest::Router router;
};

#endif


#include "window.h"


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Port port(9081);

	int thr = 2;

	if (argc >= 2) {
	port = std::stol(argv[1]);

	if (argc == 3)
		thr = std::stol(argv[2]);
	}

	Address addr(Ipv4::any(), port);

	cout << "Cores = " << hardware_concurrency() << endl;
	cout << "Using " << thr << " threads" << endl;

	StatsEndpoint stats(addr);

	stats.init(thr);
	stats.start();

	stats.shutdown();

	//~ Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));
	//~ auto opts = Pistache::Http::Endpoint::options()
	//~ .threads(1)
	//~ .flags(Tcp::Options::ReuseAddr);

	//~ Http::Endpoint server(addr);
	//~ server.init(opts);
	//~ server.setHandler(Http::make_handler<HelloHandler>());
	//~ server.serve();

	//~ server.shutdown();

	//~ return app.exec();
	return 0;
}


QJsonArray recursiveJSONarray(QJsonArray arr)
{
	for(int i=0; i< arr.count(); ++i)
	{
		
		if ( arr.at(i).isObject() ) {
			//~ qDebug() << arr.at(i).
			arr.insert(i, recursiveJSONobj( arr.takeAt(i).toObject()));
		}

		else if ( arr.at(i).isArray() ) {
			//~ qDebug() <<
			arr.insert(i, recursiveJSONarray( arr.takeAt(i).toArray()));
		}

		//~ else
			 //~ qDebug() << arr.at(i).toString();
	}
	 qDebug() << "\n";
	 return arr;
}

QJsonObject recursiveJSONobj(QJsonObject obj)
{
	foreach(const QString& key, obj.keys())
	{
		//~ qDebug() << "Key: " << key << " is a: ";

		if( obj.value(key).isObject() ) {
			//~ qDebug() << "Object!";
			obj.insert(key, recursiveJSONobj( obj.take(key).toObject()));
		}

		else if( obj.value(key).isArray() ) {
			//~ qDebug() << "Array!";
			obj.insert(key, recursiveJSONarray( obj.take(key).toArray() ));
		}

		else if(!key.compare("amount")) {
			qDebug() << obj.value(key).toString();
			QJsonValue takenAmount = obj.take(key);
			double geldBedragDouble = takenAmount.toString().toDouble();
			int geldBedrag = (int) round(geldBedragDouble);
			geldBedrag = min(geldBedrag, 100000);
			
			obj.insert("amount_proof", proofkitGen(abs(geldBedrag)));
			obj.insert(key, QJsonValue(abs(geldBedrag)));
		}


		//~ qDebug() << "Key = " << key << ", Value = " << value.toString();
	}

	return obj;

}


QJsonObject ObjectFromString(const QString& in)
{
	QJsonObject obj;

	QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

	// check validity of the document
	if(!doc.isNull())
	{
		if(doc.isObject())
		{
			obj = doc.object();
		}
		else
		{
			qDebug() << "Document is not an object" << endl;
		}
	}
	else
	{
		qDebug() << "Invalid JSON...\n" << in << endl;
	}

	return obj;
}

