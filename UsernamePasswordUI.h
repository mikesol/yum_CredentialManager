#pragma once
#include <JuceHeader.h>
#include "Types.h"

/// AppCredentials subclass by class-inline header include

struct UnamePWEditor : public TextEditor
{
    void mouseDown (const MouseEvent& e) override
    {
        jassert (onMouseDown != nullptr);
        if (onMouseDown) onMouseDown ();
        TextEditor::mouseDown (e);
    }
    std::function<void ()> onMouseDown;
};

class UsernamePasswordUI : public juce::Component
{
public:
    UsernamePasswordUI ();
    
    /// if a function is defined, then virtual function loginButtonClicked won't get a call
    std::function<void (const UsernameAndPassword&)> onLoginButtonClicked { nullptr };
    
    /// returns the current contents of the text editors.
    UsernameAndPassword getCurrentEditorCredentials ();
    
    /// after you're finished with the password editor you should reset it for good measure
    void resetPasswordEditor ();
    
    
protected:
    /// will only be called if onLoginButtonClicked == nullptr
    virtual void loginButtonClicked (const UsernameAndPassword& credentials);
    
    TextButton loginButton { "Login" };
    UnamePWEditor usernameEditor;
    UnamePWEditor passwordEditor;
    
    void resized () override;
    
    
private:
    juce::Array<juce::Component*> elements
    {
        &usernameEditor,
        &passwordEditor,
        &loginButton
    };
    
    std::unique_ptr<PopupMenu> credentialsPopup;
    
    void handleLoginButtonClick ();
    void updateCredentialsPopup (Component* source);
    void fillEditorsForKeychainUser (const Username& user);
    void closeCredentialsPopup ();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (UsernamePasswordUI)
};

