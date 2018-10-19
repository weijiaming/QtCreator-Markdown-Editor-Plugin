#ifndef MDEDITORCONSTANTS_H
#define MDEDITORCONSTANTS_H
#include <QtGlobal>
namespace MDEditor {
namespace Constants {

const char M_CONTEXT[] = "MDEditor.ContextMenu";
//const char C_MDEDITOR[] = "MDEditor.MarkdownEditor";
const char MDEditor_ID[] = "MDEditor.MarkdownEditor";
const char MDDocument_ID[] = "MDEditor.MarkdownFile";
const char MDEditor_DISPLAY_NAME[] = QT_TRANSLATE_NOOP("OpenWith::Editors", "MarkdownEditor");
const char SWITCH_DECLARATION_DEFINITION[] = "MDEditor.SwitchDeclarationDefinition";
const char OPEN_DECLARATION_DEFINITION_IN_NEXT_SPLIT[] = "MDEditor.OpenDeclarationDefinitionInNextSplit";
const char RENAME_SYMBOL_UNDER_CURSOR[] = "MDEditor.RenameSymbolUnderCursor";
const char FIND_USAGES[] = "MDEditor.FindUsages";
const char OPEN_PREPROCESSOR_DIALOG[] = "MDEditor.OpenPreprocessorDialog";
const char M_REFACTORING_MENU_INSERTION_POINT[] = "MDEditor.RefactorGroup";
const char UPDATE_CODEMODEL[] = "MDEditor.UpdateCodeModel";
// const char INSPECT_CPP_CODEMODEL[] = "MDEditor.InspectCppCodeModel";

//const int TYPE_HIERARCHY_PRIORITY = 700;
//const char TYPE_HIERARCHY_ID[] = "MDEditor.TypeHierarchy";
//const char OPEN_TYPE_HIERARCHY[] = "MDEditor.OpenTypeHierarchy";

//const int INCLUDE_HIERARCHY_PRIORITY = 800;
//const char INCLUDE_HIERARCHY_ID[] = "MDEditor.IncludeHierarchy";
//const char OPEN_INCLUDE_HIERARCHY[] = "MDEditor.OpenIncludeHierarchy";

const char MD_SOURCE_MIMETYPE[] = "text/markdown";
const char MDX_SOURCE_MIMETYPE[] = "text/x-markdown";

const char WIZARD_CATEGORY[] = "O.Markdown";
const char WIZARD_TR_CATEGORY[] = QT_TRANSLATE_NOOP("MDEditor", "Markdown");

const char MD_SNIPPETS_GROUP_ID[] = "Markdown";

//const char MD_PREPROCESSOR_PROJECT_PREFIX[] = "CppPreprocessorProject-";
} // namespace MDEditor
} // namespace Constants

#endif // MDEDITORCONSTANTS_H

