#include <boost/test/unit_test.hpp>

#include "util.h"
#include "scrypt.h"
#include "main.h"

BOOST_AUTO_TEST_SUITE(scrypt_tests)

BOOST_AUTO_TEST_CASE(scrypt_hashtest)
{
    // Test Scrypt hash with known inputs against expected outputs for all 
    // supported Nfactors, only goes up to N = 1048576 due to current 32 bit
    // limit on nTime. Blocktime is packed in the pseudoheaders in inputhex
    #define HASHCOUNT 50
    const char* inputhex[HASHCOUNT] = {
        "020000008ee25a9268394afb1f7e51bab5b464d465f2432b8f8225d1365526d987a81fb93c26d1e36f7fae412d4249d710b5954c57d9d4aeef8434d775fade931be615bd6921cf52d788a9542003e778", // N = 2048
        "02000000c41f5d7e841fa765af9801bed84925c5e3eb73d216796a84a8f9dbb2cf55bf30cce01982b1f81506bff80ab261ee8eb592ad9fcb982b8cd4f4917cd0d3da9eef6921cf5263da1a99f9d697aa", // N = 2048
        "02000000b94de83925e77e053b0edbd94fe3a9dcf6c4f1b2885d2ada8006a5dd6714e947f4f2796e9c72666bde6821064dddcfad85601d99cb0f09c65b605690f0f1e7056921cf520f6bcd98c11bea16", // N = 2048
        "0200000055ee27fe874a5bc20ef90b29efd0f0be9eb2e4cee9ae1ea9ae6923e7bda375a634a5dd0df550fb1bf39f6404f7b488db34eeef0899a4a1b590fc5b05d67e5da16921cf5276aac4d343c69ea5", // N = 2048
        "02000000f6f4cf52deca4234711aa34947c1a3eab8a4e3da2bbb129a9db30cae77856c40415d9b6217e19766418c38104af9d9412c660d291af610ca0672fc11c2eb38746921cf5291f1446a54e0fe86", // N = 2048
        "02000000d984f27409a31522c8f248e1e93e42e205e13049f84658d9e2a9e9738f6998dbd8a38d299e8b472cb04f41f249808be77adfeb5cbe840c71d6f28507ddca982e6921cf562bab641f41b570b8", // N = 4096
        "020000005f3572a0865caf8c495ae9edb54380d2121bce682a774630a04e2593dc521e89504439fe938d6bdade7aec81249fa568b245d929efb33b58efc89300341839066921cf5601bf29f059edb6f1", // N = 4096
        "0200000009589e0a940b7b048dfe400217593ed4bc434b2fdf57ebb7f7067dd3feba3f917fa2b17e03abcfbe3df9ef2ba970316d19c655576a10a4df20073b80c93bcdf46921cf56457ee1e8a78651ad", // N = 4096
        "02000000c56698ed15e7fd53b0027f2df0b3ac0b922bc22cd27c695c9ae5902efcc6f46e0e3fb4611887d0424442b05b4c38b5dbd6365e27c5629ef94cb228d6a3a7593b6921cf56d0a4bf9a079b091c", // N = 4096
        "02000000dd1ec75279e481cdb2a34568340124421c36e1ba0b5208b18171068dd897a5d6bc42f88f27e570d722bbc22f6c8f8c72aecc589a5486b0f07ee7fa84f6b2c3846921cf5601b4a71fe3691530", // N = 4096
        "0200000080d1c421af38c762638ca690d5ec8f141c058c31b8a37bd1960f701ef64a49f6d5fded01e69e44ceba86aa1adaa32b8d705a800af567de232dbb1387728b6cef6921cf597e2f0c1c4bc9fe80", // N = 8192
        "0200000021cb74e8d62bbccf71849a24f8c8b527d79a689a611976e05b190b8c765018d99e09573b837783bb1d74b3a43fd60108a5c3d1916bf2f3c18292bc24009fa5376921cf59fd35405272fed975", // N = 8192
        "02000000a760c9fe8fb8d1875848197fd5a09e4d9e2b9f7c96bd47d78d2c96ecb584d6d52c026df5e7dd04bee1a9596d5af0a04c9d30740b6e8e8a259715ab66bbf228e76921cf59f1765b0fe6742cce", // N = 8192
        "0200000089308205b451734231609dd7e842aced72757221875e377fd167daf2aa5388ad6f030c69a766aa019fefbb48b1a7e06bdc9e0fd65fe90b29aba17fb8b967a5316921cf5906fab7a2403fe0d1", // N = 8192
        "02000000f1d87c3aaad2ecfe83c0b64248934096b1efa3b371d8e34440a3a8ee0d5e712c164d7c1b10b8ec61211a60c8707a0aa6cc87b11e0736aa5c2736d109d9b879186921cf59b8d609282ee6e178", // N = 8192
        "020000005dcacd73aa4a6688c2dbeaa995c6b8d2c76346c3846bbb70a12cd930452af5914f5e267e5bd2b8833dd9aae23e25d754fb408ff0affe3b19d04cbba39040c3e26921cf5c1d0b9ea6fcf65ff1", // N = 16384
        "020000007869300631d90c519bffd9454201563f295f240ee97bfe7ffd155f6fdb686c30d2a1ebc691d6cedfedc3c19bf3cdc8cce95f5a2634124b1148b3d7ce2a474be56921cf5c04af34b80d6d761a", // N = 16384
        "02000000d257dddd8b2cad3a25a65957f720690346c256755aa53a3eb4442f56c607dd71c1b040cfe9182bffa3e9b4b826bf3904609b5b48f5e21becf36d50f44f4278bc6921cf5c88a97d3e4482a758", // N = 16384
        "020000001f3527150cab77ed5cda7c0e1e2245be253a71d91c531babfba5963420939bd74b3bb2cb5e29c00c76859a1ff974cd5a18db397e83fb9c5ba911680cb63d52b76921cf5c9b1e25fbdfa71215", // N = 16384
        "02000000df17ab60aa5cd0e30601d25023366699cba276755bf3451d37b9fb332f8ede29312bd9da4eb39a6d9d79e08413c74410c53f35ca36b093f732dcd25adb0cf9166921cf5c51b559f499c62c0d", // N = 16384
        "02000000cd17cf9973e4b69e366fc774b190b38abfbc3a554def6881486ec8f81d6b6f23a766f4ae0dbc08abcd88465b3f777475ba59ab10d79e2c4ae1458e703256fcba6921cf62e271322aea8cddfa", // N = 32768
        "02000000117c89e48a7491db4555958765bd43119f573a9eab65feeb67fb35c3b974ab285b9ed13c04497495e593f35320199f61151613845ef036995322d51528dd58276921cf62b303bcb8d7717cc2", // N = 32768
        "02000000b945b11782f97320212b77340dfc493c0a361bff9af2b7183fb6f69b1ad5fefed7de9233d5bafc819eda05515f5d949e60dfe92051c6bb09293b91710e5ec2c16921cf62f8531e9f47df45da", // N = 32768
        "02000000a9f2b9e2b4e937879172a4edca5b6f057fb828c89a15575c53d2a96a0bf68a3ce191e8653e93b60b1906cb0ba1a25fd9780d4dc6d83adda1618b4f1825a411996921cf620c171c08ecdc83f9", // N = 32768
        "02000000fc2b5b1a6bc486f9a505a8b6c2f4122b7886b5e4fa5512f71936f538192d052f38a99acd9895aa849d034fc998c7b1c1bd32b14cf6462604461f7752625aa1356921cf627d8babfa56f1fa01", // N = 32768
        "02000000eec6e3d0eaad6993704dd0fde72f1ee4fdcb657ea6c869bf596de936c22a03a51f115d8872c408917301db48c8281fe54d8267ad5ecf3257552dd0589bfcf7216921cf6ea7d35091e5d1a922", // N = 65536
        "020000009e6bdf99e6654f09cad583165d43b5115c40f5dcb34762540544f677cec5032e74561771d4d13cba50272cf0d1c7d058b84f1912f6845e87266d617d6d9f3c916921cf6e9860adb5e5719aa9", // N = 65536
        "02000000ed88fc963de8116811fafa7398fb94d1422ee207898788ec3261674588134ed0fd51b4446e285da9409f5b62a8319ef2d2ae49020cd93e845aa6e384d371a1d66921cf6e35745026708da87b", // N = 65536
        "0200000051a1ce804b38b608ca2792cf2814243f11100a6f23ccc4726b92f20bd4849a2ea37ead2efd6101e7132baeff0ec8cf8ce0b49a99cdddab9cb42bc22b8cc9e8326921cf6ef3a8a72296b2c0fa", // N = 65536
        "020000008efc9548080ce650d70b3da7ee7c7aca65dcadf8108882913abdc01ba97d642c6e896c23e7663c1eff0583c1f2ee0ab9bbcf956354f876d30e8f1842ac39fc336921cf6e2e5c59fdd8faba30", // N = 65536
        "0200000097f620292ca8d94283ef5ca07416dd5b7071c29073af8e05ee821de070d00b8a7e34286ebbb42f87e64ef3beef2c9cff93eabdd665820f560c7472c16252b1456921cf7a34ec9c781d288711", // N = 131072
        "02000000593fcb0f593a3280c1793db3c59004a183460d88dc67e7caad0d7543e7b026228653b5ab7913f4224f776e10b01ca0900e2c159785eb49f84196c3b9325880ff6921cf7ac805ffa8165b1306", // N = 131072
        "02000000e68266d47c61b2db63e9016d846bdcf061002acc108330a5dc416705d989053fe54cd79cf17766e1fefff531949f28e322d6e5ce437f70a30ae488eceed1320b6921cf7aecfe922a31c44c40", // N = 131072
        "02000000003a0d1a6c5922420c52ec12f5188dae71eeef605f8d803bbdff8b5d62f797d74d78ea84031ebf31bdb528149a8f0fa7c92f6d653252fbe4a0711d2df9d88d226921cf7a704e54a00c9bbd19", // N = 131072
        "0200000072b2157a4bc26e6a7ba64db0ea5b25d363ff0e5dcf8569ac78f260e124c414f8cfba45b0389ab4f6e8e6c4472d754048d6cc2468cfde70cf53437cf7f22d3f0c6921cf7aca437bb69f28b04e", // N = 131072
        "020000006dd892dcba7cd4050bbd1d3fcd4e8abf204c0eeb0bb8c21fa5fe52738deea135c1fc97d7446801792bf88e43aa49aa7bc5b048d0f810a6de1a0c9420b13624ef6921cf9279048871ec42585a", // N = 262144
        "020000004b0999051741d8f869696a51c8d3613ee88c94bbf234a24df96613e1af2861c3c07d2846424152f0f0200af54b61abf4b196d10d7c2c948fcdd31454e599733e6921cf925cdbed04e204ee0c", // N = 262144
        "0200000036e51aebdba781520606108e6f37b98d73e7387a4b26a6d4726f5646a927205baaef93b05a6ad2e972128c88ba854c68485ccaab70832742c5260eb1642c39336921cf926061ae15675db251", // N = 262144
        "02000000e4148d253d3e289bcd431d32b36510970b9b4025c23d9139d236413f59bb563a69f7635914c8dfec8c83cd94b6b532d04d026eebdbd24a52b85becea313a51476921cf9286b509a5c965fe59", // N = 262144
        "020000005f8c45e3d8105c0e1d961ca166b6e616ae4d10bbaf217c96b469125f0350f1a0232faab6cdcdff5ac0a4b76513613d1e85d213520f870cd3c6b6de05e0fa7d676921cf92e192b03e64d9f1a4", // N = 262144
        "020000001da872bd01b957ac228242e879c85a2a26d7752704bb360bb12401ee756678f2a309ecaaa8af7b6cd3c80d6657f7f530f9986e8e8da05fe58b90ea4f1c49163d6921cfb25b67edbd45191790", // N = 524288
        "02000000136db56f6a49ec511c877d1a2c16534e2117fbb5bda507b5fdc49550d531de0366fb852d26a6ea81779ed15bb1084fad6bfbfe43ca4e0c89f42f68840c0274e96921cfb27f84945f35c67c61", // N = 524288
        "02000000645cda2326b5e82c1e68cb4964596bc8fca1a62551844ea3a5aea65d29f35b86fa0b09c69ba83ff93a3837e0715eb30d5ab74b7ddcd958dad364a670894552c86921cfb2f6ff0eb69fae4e7a", // N = 524288
        "020000001d1607c04d12db8211769bebb8189602aafec2abbd0f2245c7d0d6e638cb7d20290b0f8361a98ddf8d0496d6136c36598037ee1dbfa1c0c7daf39af593fea14d6921cfb25a2b833c6bc8864e", // N = 524288
        "02000000b9f070d13bdc6aef685b8d7e9396bbee4d2c9d1006ea33a786efa9f5dda7fd86b00ef057c7ea0825a380ec7e842631aae0f7ec45cf0cbfe1ee3c59c241618b546921cfb2ada471f2cb4ae9de", // N = 524288
        "02000000c52837c35d9ec27f91e25c577d281b667d47c552d10ba31db31c8064e22acdd71eaa28ff543cf7abe33f28c57edeca9ecf54a4d716b589e7a3101d2a7096b57d6921cfd2b74d83c0d829486c", // N = 1048576
        "0200000040a72e631e21d9e349c64a41b3b0da09ea73fc5d376c1a9c37429faac82bd0cecf789a3ad8a32b32aa805c9a4e14bedea9b749dc95e09923aec02baf93ec754e6921cfd2c0322b8786df0a70", // N = 1048576
        "02000000898dd5d2edb905aee8eae8a1bb377ee410a84953bcc6c47d2378753152422bb9c88f9a22edd8d7681a0c929937f468885ea7111b439d496ab95a5308e08a76596921cfd23949caabc83328bf", // N = 1048576
        "02000000b3adaae98f3a3d2462695f529b050b8eb39d13f5f840ccaf564d75d413f00e378f6a4de95c45fb6964937d368727d7cf7fffeb1db528bf393b65a75c57b4b0d26921cfd2737f3b829deb8e2d", // N = 1048576
        "0200000081eb601cb1c719931f4fa1a52a82bcf0809a28f7e8c39a2a2c65dcdd997e12dad3de00d69a0dcf7384f2d988b0e3e471009743bd8b7fa1847dab0663a5af33b26921cfd25a7210de12686839" // N = 1048576
    }; 
    const char* expected[HASHCOUNT] = { 
        "5edeed871140e20f3aab48ec1e372e61383c5d5d1518b77c51fe633210347ba0",
        "eef43435a4483e652f4d5a1ff150875da217e4a46a6e80c60409f101db925e6a",
        "0567a62caa50e90a8b9310cce686ee6c50c3dd07227216f41ed03145d52cab91",
        "ace0f14d63786072174c303dcc8483cfd98e5e2b2d806eca755413564e64a929",
        "4e94673cde1ff0544af1f7f8c3eb10fba937aab3faed766ff54c17fd127c7893",
        "4c8703f40d96a551389f299c524d4bc5d63e9fde07837a8d3aea0716dc741806",
        "e5c988f957f674eeb3c4c5e7e4128ae1dc5342adb229434d4fbadad4c07713c6",
        "922f0988628e8e8d98984e2a0213b0edebb61fc975ae1fe0485a297a552e79c0",
        "fba61dbac8ed11942e581193f7c5cc8fbb2404c0726a2e3a8df94e220b879283",
        "4b8bc70aa5a47794ae82315506c57688093c816ea8859d0865d3cc12dc5b7edb",
        "289d68e6f5de08cabdeb16f3ad307070bdd7b9d544e86ec3fcd91dded0649633",
        "0d04720a27146ae4643dbadaeda25d145a72a6cd936f8ebdf5d33cc6d65b8571",
        "b221b5524feab9c2c4db93907cf12768cab4c546484174eef73ea5ae8c332649",
        "0338c7f2aec688d6a232891a2f6fc1dc3d55ee081ae67c3549bab888bc5e83a4",
        "c0785df4d8d122f05f92a32c156be5c271fa136fb9f4b98474145a531e86895d",
        "34f4641a99f063756403fcc1d5101429881238a63845a3fc7b3e924a001ce65f",
        "fca15fa3f65847aa869ffd6ccb1e0cc3ae0c838423bf3d45c144adb78ccb9d56",
        "e52f093859391f3f252ec972b6fa5b55db16759ba32d225120c79194e1db4ddc",
        "82c961442ac0472d12df820aabf6fdca90e41237ca5c18f561b118a98a527c25",
        "26492bc3b320d40ae88d0cf254d928dc02a159d76b00ee99f1debed60cb8cc37",
        "55477047367baea08ab8f5b09986d5dc64be81e4c86838d6a4d222964c611348",
        "5d89b57e16970df67d217255e7cec5f7ff2f1d39a68ada075e707ae2789eb52b",
        "c436b4e35d3e2495c57bd5c70f1710c209bfebf22202396c2b854f1828c6ae99",
        "b207429494d13bc80c623140d0039c829faaaad3f57e77014a851581c124f995",
        "5488849af7dfce420e88a6b98dc570e7162718a5f1c9e7d022606731829f6553",
        "f0c5a5c013909d8a8d59a15743c2aa4081027680624c18efd67c69d9342d7473",
        "df0e5c0048e7bfcb13467d883e936563174c97ca7bc1207d371c22317332ac64",
        "fc59a251a6c61cc655b052d6fd79d4ca2911c1da6c3e54ce860a6a4698bb1a9e",
        "6229e93260be8e28a54441ed863177c77d872fd99538d492524f717889df868c",
        "b23f8b1563eddb26c5b991576d70e412ff9ef0a79f2f7bfc68e4d4a69d2d532d",
        "6a502a8bbef2cbb523ba4b67bdfb38745229ac6be6dd591bb6362f7b20679d90",
        "071e449b35de00fa8d675b7124fdbec519d780ead661a13f34e0bc03c16798c2",
        "1fa905f8aab2a11c80c668b07bbb138c7c76351dbfafc10092dcbd31d5f8246d",
        "b4e1d8994c706608aee26ee717294bcb135738af74adceabe1969aaaad515a6e",
        "5194404cd3efd4a3170b6ed9b5418cffcd245c625dd7c3b6c0e3b9c104b3fb0b",
        "f3bcdf85afb097140722aa5d393ad483d2bbd25906a8618b542cc06c5d333656",
        "b49197cf94b6446c5c919139c93b814d194803a2b151e5c17a92dc145b79f1dd",
        "6f84eb1b9e73277d26aab8cf0ebdd5ccd82f4ae99ee021af3c669fee18657d81",
        "902bca92c68fe89986e0254565a24aeb16a70540987b99439455ccdffce9a2ee",
        "4cd927541cc8aae9a5296203518cbc008a66568b7ebd39707411f3fe3f05de16",
        "856306439d9de76dc3c05428fc230e2cf68db2a1824420eb89bc9d987d82a7f3",
        "098d83a6b8aeb8acbc7e499596702b37316fb3b2d904329f4169770c54de5e42",
        "f6ce35cf91a04f344ee4c2dd1d1a2852b91722ce53c0b933745e6382ee18fcad",
        "ac349d2ab08b7f81492efa40a56922d0c6e14a167a8f10bae5ff735333cfd6a7",
        "ece6260edafaabfec928eb44029d00246e35a934b923f468a00dad74afa88554",
        "16c6d802403284f5e976796086fa7b75a226fa53e685da4635e8fb75040772de",
        "234e45be88fceb1564f0966acd5c10ae60afce23f4aa4e1f5a957fff177e675e",
        "968de389893b4249d80a24c558cf7aca2d01c59874e8064591cba9da61653169",
        "1a1c0481ccacf32df5c54e5e7da0fb4970cd0ed6b6381b8aa0099d163d62f733",
        "723148d84ff10eed10f0a0ed62912761c7b3fb302ebcbda269199c52071e995e"
    };
    uint256 scrypthash;
    std::vector<unsigned char> inputbytes;
    
    for (int i = 0; i < HASHCOUNT; i++) {
        inputbytes = ParseHex(inputhex[i]);
        unsigned int blocktime = *(unsigned int*)(&inputbytes[68]);
        printf("%i\n", blocktime);
        unsigned char Nfactor = GetNfactor(blocktime);
        unsigned int scratchpad_size = 128 * (1 << (Nfactor+1)) + 512;
        std::vector<char> scratchpad = std::vector<char>(scratchpad_size);
#if defined(USE_SSE2)
        // Test SSE2 scrypt
        scrypt_N_1_1_256_sp_sse2((const char*)&inputbytes[0], 
                                BEGIN(scrypthash), &scratchpad[0], 
                                Nfactor);
#endif
        // Test generic scrypt
        scrypt_N_1_1_256_sp_generic((const char*)&inputbytes[0], 
                                    BEGIN(scrypthash), &scratchpad[0], 
                                    Nfactor);
        BOOST_CHECK_EQUAL(scrypthash.ToString().c_str(), expected[i]);
    }
}

BOOST_AUTO_TEST_SUITE_END()
