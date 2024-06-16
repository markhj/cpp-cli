#pragma once

#include <bbunit/bbunit.hpp>
#include "test-emitter.hpp"
#include "test-tools.hpp"

using CppCLI::CLI;
using CppCLI::Response;

class BaseTestCase : public BBUnit::TestCase,
                     public TestTools {
public:
    BaseTestCase() : m_testEmitter(std::make_shared<TestEmitter>(TestEmitter())),
                     m_cli(CLI("Test CLI", "v0.0.1", m_testEmitter)) {
        m_cli.setErrorHandler([](std::shared_ptr<ConsoleIO> io, std::runtime_error &) -> Response {
            return {};
        });
    }

    void test();

protected:
    virtual void configure(CLI &cli) = 0;

    virtual void run() = 0;

    void testCmd(const std::string &cmd, const std::function<void(const Response &)> &assertions);

    std::shared_ptr<TestEmitter> m_testEmitter;

    CLI m_cli;
};