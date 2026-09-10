template <typename T>

class BaseSingleton {
protected:
  BaseSingleton() = default;
  ~BaseSingleton() = default;
  BaseSingleton &operator=(const BaseSingleton &) = delete;
  BaseSingleton(const BaseSingleton &) = delete;

public:
  static T &getInstance() {
    static T instance;
    return instance;
  }
};

#define MAKESINGLETON(class_name)                                              \
private:                                                                       \
  class_name();                                                                \
  class_name &operator=(const class_name &) = delete;                          \
  class_name(const class_name &) = delete;                                     \
                                                                               \
  friend class BaseSingleton<class_name>;
