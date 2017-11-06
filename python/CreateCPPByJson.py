import json

def CreateCppFile(fileName, JsonData):
    with open(fileName, "w") as f:
        f.write("#ifndef __XJTRADEPLATFORM_NETWORK_PROTOCOL_H__\n")
        f.write("#define __XJTRADEPLATFORM_NETWORK_PROTOCOL_H__\n")
        f.write("#include \"../Json/json.h\"\n")
        f.write("#include <string>\n")
        f.write("using namespace std;\n\n")
        head = list((JsonData.items()))[0]
        for k, v in JsonData.items():
            f.write("struct " + k + "\n{\n") if head[0] == k else f.write("struct " + k + " : public " + head[0] +"\n{\n")
            for ik, iv in v.items():
                if isinstance(iv, bool):
                    f.write("   bool " + ik + " = "+ ("true" if iv else "false") +";\n")
                elif type(iv) == type(None):
                    f.write("   string " + ik + ";\n")
                elif isinstance(iv, float):
                    f.write("   double " + ik + " = " + str(iv) + ";\n")
                elif isinstance(iv, int):
                    f.write("   int " + ik + " = " + str(iv) + ";\n")

            f.write("\n   virtual void to_object(string strJsonData)\n")
            f.write("   {\n")
            f.write("       Json::Reader rd;\n")
            f.write("       Json::Value root;\n\n")
            f.write("       rd.parse(strJsonData, root);\n")

            if k != head[0]:
                for hk in head[1]:
                    if isinstance(head[1][hk], bool):
                        f.write("       " + hk + " = root[\"" + hk + "\"].asBool();\n")
                    elif isinstance(head[1][hk], int):
                        f.write("       " + hk + " = root[\"" + hk +"\"].asInt();\n")
                    elif type(head[1][hk]) == type(None):
                        f.write("       " + hk + " = root[\"" + hk + "\"].asString();\n")
                    elif isinstance(head[1][hk], float):
                        f.write("       " + hk + " = root[\"" + hk + "\"].asDouble();\n")

            for ik, iv in v.items():
                if isinstance(iv, bool):
                    f.write("       " + ik + " = root[\"" + ik + "\"].asBool();\n")
                elif isinstance(iv, int):
                    f.write("       " + ik + " = root[\"" + ik +"\"].asInt();\n")
                elif type(iv) == type(None):
                    f.write("       " + ik + " = root[\"" + ik + "\"].asString();\n")
                elif isinstance(iv, float):
                    f.write("       " + ik + " = root[\"" + ik + "\"].asDouble();\n")
            f.write("   }\n\n")

            f.write("   virtual string to_string()\n")
            f.write("   {\n")
            f.write("       Json::FastWriter fw;\n")
            f.write("       Json::Value root;\n\n")

            if k != head[0]:
                for hk in head[1]:
                    f.write("       root[\"" + hk + "\"] = " + hk + ";\n")

            for ik, iv in v.items():
                    f.write("       root[\"" + ik + "\"] = " + ik + ";\n")
            f.write("       return fw.write(root);\n")
            f.write("   }\n")

            f.write("};\n\n")
        f.write("#endif")
        f.close()


def ReadJsonFile(filename):
    with open(filename, "r", encoding= 'utf-8') as jsonfile:
        JsonData = json.load(jsonfile)
        return JsonData

if __name__ == "__main__":
    JsonData = ReadJsonFile("XJTradePlatform_network_protocol.json")
    CreateCppFile("XJTradePlatform_network_protocol.h", JsonData)