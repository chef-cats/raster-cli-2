#pragma once
#include <images/Netpbm.hpp>


/**
 * NetpbmWithMaxValue present Netpbm image with
 * additional paramenter max_value. This paramenter defined range of possible
 * values for each pixel between black and white - [0, max_value]. Black is 0 and
 * max_value is white. The possible values for max_value are into the
 * [1, 255].
 *
 */
class NetpbmWithMaxValue : public Netpbm {
  public:
    NetpbmWithMaxValue(const std::string& file_name);
    NetpbmWithMaxValue(const NetpbmWithMaxValue& other) = default;
    NetpbmWithMaxValue(NetpbmWithMaxValue&& other) = default;
    NetpbmWithMaxValue& operator=(const NetpbmWithMaxValue& rhs) = default;
    NetpbmWithMaxValue& operator=(NetpbmWithMaxValue&& rhs) = default;
    virtual ~NetpbmWithMaxValue() = default;

  public:
    virtual void apply(const Operation& operation) = 0;
    virtual void load() = 0;
    virtual void save() const = 0;

  public:
    size_t get_max_value() const;

  protected:
    virtual void metadata_check() const override;
    virtual void load_metadata(std::ifstream& file) override;
    virtual void save_metadata(std::ofstream& file) const override;

  protected:
    void set_max_value(size_t max_value);

  private:
    DelayLoad<size_t> _max_value;
};