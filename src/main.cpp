

#include <memory>
#include <cpptrace/from_current.hpp>
#include <version/version.hpp>

#include "common/ImGuiLogDebugLog.hpp"
#include "common/Logger.hpp"
#include "gamer/Gamer.hpp"

int main(int argc, char *argv[]) {
    CPPTRACE_TRY
        {
            logger->info(game::version());
            auto game = game::Gamer::create_game(logger);
            game.run();
        }
    CPPTRACE_CATCH(std::exception const &e) {
        cpptrace::from_current_exception().print();
        logger->error(e.what());
        return 1;
    }
    return 0;
}
