// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: LogSend.proto

#include "LogSend.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

namespace ik {
class LogSendRequestDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<LogSendRequest> _instance;
} _LogSendRequest_default_instance_;
class LogSendReponseDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<LogSendReponse> _instance;
} _LogSendReponse_default_instance_;
}  // namespace ik
static void InitDefaultsLogSendRequest_LogSend_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::ik::_LogSendRequest_default_instance_;
    new (ptr) ::ik::LogSendRequest();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::ik::LogSendRequest::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_LogSendRequest_LogSend_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsLogSendRequest_LogSend_2eproto}, {}};

static void InitDefaultsLogSendReponse_LogSend_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::ik::_LogSendReponse_default_instance_;
    new (ptr) ::ik::LogSendReponse();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::ik::LogSendReponse::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_LogSendReponse_LogSend_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsLogSendReponse_LogSend_2eproto}, {}};

void InitDefaults_LogSend_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_LogSendRequest_LogSend_2eproto.base);
  ::google::protobuf::internal::InitSCC(&scc_info_LogSendReponse_LogSend_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_LogSend_2eproto[2];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_LogSend_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_LogSend_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_LogSend_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ik::LogSendRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ik::LogSendRequest, node_name_),
  PROTOBUF_FIELD_OFFSET(::ik::LogSendRequest, time_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ik::LogSendReponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ik::LogSendReponse, serial_),
  PROTOBUF_FIELD_OFFSET(::ik::LogSendReponse, is_end_),
  PROTOBUF_FIELD_OFFSET(::ik::LogSendReponse, msg_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::ik::LogSendRequest)},
  { 7, -1, sizeof(::ik::LogSendReponse)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::ik::_LogSendRequest_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::ik::_LogSendReponse_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_LogSend_2eproto = {
  {}, AddDescriptors_LogSend_2eproto, "LogSend.proto", schemas,
  file_default_instances, TableStruct_LogSend_2eproto::offsets,
  file_level_metadata_LogSend_2eproto, 2, file_level_enum_descriptors_LogSend_2eproto, file_level_service_descriptors_LogSend_2eproto,
};

const char descriptor_table_protodef_LogSend_2eproto[] =
  "\n\rLogSend.proto\022\002ik\"1\n\016LogSendRequest\022\021\n"
  "\tnode_name\030\001 \001(\014\022\014\n\004time\030\002 \001(\014\"=\n\016LogSen"
  "dReponse\022\016\n\006serial\030\001 \001(\005\022\016\n\006is_end\030\002 \001(\010"
  "\022\013\n\003msg\030\003 \001(\014b\006proto3"
  ;
::google::protobuf::internal::DescriptorTable descriptor_table_LogSend_2eproto = {
  false, InitDefaults_LogSend_2eproto, 
  descriptor_table_protodef_LogSend_2eproto,
  "LogSend.proto", &assign_descriptors_table_LogSend_2eproto, 141,
};

void AddDescriptors_LogSend_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_LogSend_2eproto, deps, 0);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_LogSend_2eproto = []() { AddDescriptors_LogSend_2eproto(); return true; }();
namespace ik {

// ===================================================================

void LogSendRequest::InitAsDefaultInstance() {
}
class LogSendRequest::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int LogSendRequest::kNodeNameFieldNumber;
const int LogSendRequest::kTimeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

LogSendRequest::LogSendRequest()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ik.LogSendRequest)
}
LogSendRequest::LogSendRequest(const LogSendRequest& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  node_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.node_name().size() > 0) {
    node_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.node_name_);
  }
  time_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.time().size() > 0) {
    time_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.time_);
  }
  // @@protoc_insertion_point(copy_constructor:ik.LogSendRequest)
}

void LogSendRequest::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_LogSendRequest_LogSend_2eproto.base);
  node_name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  time_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

LogSendRequest::~LogSendRequest() {
  // @@protoc_insertion_point(destructor:ik.LogSendRequest)
  SharedDtor();
}

void LogSendRequest::SharedDtor() {
  node_name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  time_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void LogSendRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const LogSendRequest& LogSendRequest::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_LogSendRequest_LogSend_2eproto.base);
  return *internal_default_instance();
}


void LogSendRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:ik.LogSendRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  node_name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  time_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* LogSendRequest::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<LogSendRequest*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // bytes node_name = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 10) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        object = msg->mutable_node_name();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParser;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheck(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      // bytes time = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 18) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        object = msg->mutable_time();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParser;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheck(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
string_till_end:
  static_cast<::std::string*>(object)->clear();
  static_cast<::std::string*>(object)->reserve(size);
  goto len_delim_till_end;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool LogSendRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ik.LogSendRequest)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // bytes node_name = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (10 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_node_name()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // bytes time = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (18 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_time()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:ik.LogSendRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ik.LogSendRequest)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void LogSendRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ik.LogSendRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes node_name = 1;
  if (this->node_name().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      1, this->node_name(), output);
  }

  // bytes time = 2;
  if (this->time().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      2, this->time(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ik.LogSendRequest)
}

::google::protobuf::uint8* LogSendRequest::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ik.LogSendRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes node_name = 1;
  if (this->node_name().size() > 0) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        1, this->node_name(), target);
  }

  // bytes time = 2;
  if (this->time().size() > 0) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->time(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ik.LogSendRequest)
  return target;
}

size_t LogSendRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ik.LogSendRequest)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes node_name = 1;
  if (this->node_name().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::BytesSize(
        this->node_name());
  }

  // bytes time = 2;
  if (this->time().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::BytesSize(
        this->time());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void LogSendRequest::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ik.LogSendRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const LogSendRequest* source =
      ::google::protobuf::DynamicCastToGenerated<LogSendRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ik.LogSendRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ik.LogSendRequest)
    MergeFrom(*source);
  }
}

void LogSendRequest::MergeFrom(const LogSendRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ik.LogSendRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.node_name().size() > 0) {

    node_name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.node_name_);
  }
  if (from.time().size() > 0) {

    time_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.time_);
  }
}

void LogSendRequest::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ik.LogSendRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LogSendRequest::CopyFrom(const LogSendRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ik.LogSendRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LogSendRequest::IsInitialized() const {
  return true;
}

void LogSendRequest::Swap(LogSendRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void LogSendRequest::InternalSwap(LogSendRequest* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  node_name_.Swap(&other->node_name_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  time_.Swap(&other->time_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
}

::google::protobuf::Metadata LogSendRequest::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_LogSend_2eproto);
  return ::file_level_metadata_LogSend_2eproto[kIndexInFileMessages];
}


// ===================================================================

void LogSendReponse::InitAsDefaultInstance() {
}
class LogSendReponse::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int LogSendReponse::kSerialFieldNumber;
const int LogSendReponse::kIsEndFieldNumber;
const int LogSendReponse::kMsgFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

LogSendReponse::LogSendReponse()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:ik.LogSendReponse)
}
LogSendReponse::LogSendReponse(const LogSendReponse& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  msg_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.msg().size() > 0) {
    msg_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.msg_);
  }
  ::memcpy(&serial_, &from.serial_,
    static_cast<size_t>(reinterpret_cast<char*>(&is_end_) -
    reinterpret_cast<char*>(&serial_)) + sizeof(is_end_));
  // @@protoc_insertion_point(copy_constructor:ik.LogSendReponse)
}

void LogSendReponse::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_LogSendReponse_LogSend_2eproto.base);
  msg_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&serial_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&is_end_) -
      reinterpret_cast<char*>(&serial_)) + sizeof(is_end_));
}

LogSendReponse::~LogSendReponse() {
  // @@protoc_insertion_point(destructor:ik.LogSendReponse)
  SharedDtor();
}

void LogSendReponse::SharedDtor() {
  msg_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void LogSendReponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const LogSendReponse& LogSendReponse::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_LogSendReponse_LogSend_2eproto.base);
  return *internal_default_instance();
}


void LogSendReponse::Clear() {
// @@protoc_insertion_point(message_clear_start:ik.LogSendReponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  msg_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&serial_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&is_end_) -
      reinterpret_cast<char*>(&serial_)) + sizeof(is_end_));
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* LogSendReponse::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<LogSendReponse*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // int32 serial = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        msg->set_serial(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // bool is_end = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 16) goto handle_unusual;
        msg->set_is_end(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // bytes msg = 3;
      case 3: {
        if (static_cast<::google::protobuf::uint8>(tag) != 26) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        object = msg->mutable_msg();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParser;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheck(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
string_till_end:
  static_cast<::std::string*>(object)->clear();
  static_cast<::std::string*>(object)->reserve(size);
  goto len_delim_till_end;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool LogSendReponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:ik.LogSendReponse)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 serial = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &serial_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // bool is_end = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (16 & 0xFF)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &is_end_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // bytes msg = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (26 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_msg()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:ik.LogSendReponse)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:ik.LogSendReponse)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void LogSendReponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:ik.LogSendReponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 serial = 1;
  if (this->serial() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->serial(), output);
  }

  // bool is_end = 2;
  if (this->is_end() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->is_end(), output);
  }

  // bytes msg = 3;
  if (this->msg().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      3, this->msg(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:ik.LogSendReponse)
}

::google::protobuf::uint8* LogSendReponse::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:ik.LogSendReponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 serial = 1;
  if (this->serial() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->serial(), target);
  }

  // bool is_end = 2;
  if (this->is_end() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->is_end(), target);
  }

  // bytes msg = 3;
  if (this->msg().size() > 0) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->msg(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ik.LogSendReponse)
  return target;
}

size_t LogSendReponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ik.LogSendReponse)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes msg = 3;
  if (this->msg().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::BytesSize(
        this->msg());
  }

  // int32 serial = 1;
  if (this->serial() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->serial());
  }

  // bool is_end = 2;
  if (this->is_end() != 0) {
    total_size += 1 + 1;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void LogSendReponse::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ik.LogSendReponse)
  GOOGLE_DCHECK_NE(&from, this);
  const LogSendReponse* source =
      ::google::protobuf::DynamicCastToGenerated<LogSendReponse>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ik.LogSendReponse)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ik.LogSendReponse)
    MergeFrom(*source);
  }
}

void LogSendReponse::MergeFrom(const LogSendReponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ik.LogSendReponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.msg().size() > 0) {

    msg_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.msg_);
  }
  if (from.serial() != 0) {
    set_serial(from.serial());
  }
  if (from.is_end() != 0) {
    set_is_end(from.is_end());
  }
}

void LogSendReponse::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ik.LogSendReponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void LogSendReponse::CopyFrom(const LogSendReponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ik.LogSendReponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LogSendReponse::IsInitialized() const {
  return true;
}

void LogSendReponse::Swap(LogSendReponse* other) {
  if (other == this) return;
  InternalSwap(other);
}
void LogSendReponse::InternalSwap(LogSendReponse* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  msg_.Swap(&other->msg_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(serial_, other->serial_);
  swap(is_end_, other->is_end_);
}

::google::protobuf::Metadata LogSendReponse::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_LogSend_2eproto);
  return ::file_level_metadata_LogSend_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace ik
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::ik::LogSendRequest* Arena::CreateMaybeMessage< ::ik::LogSendRequest >(Arena* arena) {
  return Arena::CreateInternal< ::ik::LogSendRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::ik::LogSendReponse* Arena::CreateMaybeMessage< ::ik::LogSendReponse >(Arena* arena) {
  return Arena::CreateInternal< ::ik::LogSendReponse >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
