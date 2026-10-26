#pragma once

class GraphIterator {
public:
    virtual ~GraphIterator() = default;
    [[nodiscard]] virtual bool hasNext() const = 0;
    virtual int next() = 0;
};
