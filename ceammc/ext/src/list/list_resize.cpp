#include "list_resize.h"
#include "ceammc_factory.h"

static const size_t MAX_SIZE = 1024;

static t_symbol* SYM_PAD;
static t_symbol* SYM_CLIP;
static t_symbol* SYM_WRAP;
static t_symbol* SYM_FOLD;

ListResize::ListResize(const PdArgs& a)
    : BaseObject(a)
    , size_(nullptr)
    , method_(nullptr)
    , pad_(0.f)
{
    createInlet();
    createOutlet();
    initProperties();
}

void ListResize::onInlet(size_t n, const AtomList& l)
{
    if (n != 1)
        return;

    size_->set(l);
}

void ListResize::onList(const AtomList& l)
{
    AtomList tmp(l);
    const t_symbol* m = method_->value();
    const size_t n = size_->value();

    if (n > MAX_SIZE) {
        OBJ_ERR << "size is too big: " << n;
        return;
    }

    if (m == SYM_PAD) {
        tmp.resizePad(n, pad_);
    } else if (m == SYM_CLIP) {
        tmp.resizeClip(n);
    } else if (m == SYM_WRAP) {
        tmp.resizeWrap(n);
    } else if (m == SYM_FOLD) {
        tmp.resizeFold(n);
    }

    listTo(0, tmp);
}

void ListResize::initProperties()
{
    size_ = new SizeTProperty("@size", size_t(positionalFloatArgument(0, 0)), false);
    createProperty(size_);

    // resize methods:
    // @clip - pad with last element (by default)
    // @pad - pad with specified value (@pad_value property)
    // @wrap - pad with wrapped values
    // @fold - pad with fold values
    method_ = new SymbolEnumProperty("@method", SYM_PAD);
    method_->appendEnum(SYM_CLIP);
    method_->appendEnum(SYM_WRAP);
    method_->appendEnum(SYM_FOLD);
    createProperty(method_);

    // adding aliases
    createProperty(new SymbolEnumAlias("@pad", method_, SYM_PAD));
    createProperty(new SymbolEnumAlias("@clip", method_, SYM_CLIP));
    createProperty(new SymbolEnumAlias("@wrap", method_, SYM_WRAP));
    createProperty(new SymbolEnumAlias("@fold", method_, SYM_FOLD));

    createCbProperty("@pad", &ListResize::getPadValue, &ListResize::setPadValue);
}

AtomList ListResize::getPadValue() const
{
    return listFrom(pad_);
}

void ListResize::setPadValue(const AtomList& l)
{
    pad_ = atomlistToValue<Atom>(l, Atom(0.f));
    method_->setValue(SYM_PAD);
}

void setup_list_resize()
{
    SYM_PAD = gensym("pad");
    SYM_CLIP = gensym("clip");
    SYM_WRAP = gensym("wrap");
    SYM_FOLD = gensym("fold");

    ObjectFactory<ListResize> obj("list.resize");
}
