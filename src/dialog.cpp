#include "dialog.hpp"

std::string TFMDialog::receive(const std::string& message) {
    m_rows.append(message);
    std::ostringstream os;
    char c;
    while (1) {
        std::cin.get(c);
        if (c == '\r' || c == '\n') {
            break;
        }

        if (std::isprint(c)) {
            os << c;
        }
    }
    return os.str();
}
