#include <nlohmann/json.hpp>

std::string to_cpp(const nlohmann::json& j, int indent = 0) {
    std::string space(indent, ' ');
    if (j.is_object()) {
        std::string s = "{\n";
        bool first = true;
        for (auto it = j.begin(); it != j.end(); ++it) {
            if (!first)
                s += ",\n";
            first = false;
            s += space + "    {\"" + it.key() + "\", " + to_cpp(it.value(), indent + 4) + "}";
        }
        s += "\n" + space + "}";
        return s;
    } else if (j.is_array()) {
        std::string s = "{";
        for (size_t i = 0; i < j.size(); ++i) {
            if (i > 0)
                s += ", ";
            s += to_cpp(j[i], indent + 4);
        }
        s += "}";
        return s;
    } else if (j.is_string()) {
        return "\"" + j.get<std::string>() + "\"";
    } else if (j.is_boolean()) {
        return j.get<bool>() ? "true" : "false";
    } else if (j.is_number()) {
        return j.dump();
    } else if (j.is_null()) {
        return "nullptr";
    } else {
        return "\"[Unsupported]\"";
    }
}

void to_cpp(std::istream& in, std::ostream& out) {
    nlohmann::json j;
    in >> j;
    out << "#include <nlohmann/json.hpp>\n";
    out << "nlohmann::json j = " << to_cpp(j) << ";\n";
}