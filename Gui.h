#pragma once

#include "imgui/imgui.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

class AppGUI {
private:
    RealEstateAgency& agency;
    bool loggedIn = false;
    string currentUsername;
    UserRole currentRole;

    char loginUser[128] = "";
    char loginPass[128] = "";
    string loginError;

    enum class View { 
        None, Properties, Clients, Agents, Transactions, Contracts, Users, Reports
    };
    View currentView = View::None;

    // Search buffers
    char propSearch[128] = "";
    bool showAdvancedSearch = false;
    double searchMinPrice = 0.0;
    double searchMaxPrice = 0.0;
    int searchType = -1; // -1: Any, 0: Apartment, 1: Villa, 2: Office, 3: Land
    int searchStatus = -1; // -1: Any, 0: Available, 1: Sold, 2: Rented

    char clientSearch[128] = "";
    char agentSearch[128] = "";
    char contractSearch[128] = "";

    // Add Property buffers
    bool showAddPropertyModal = false;
    int addPropID = 0;
    int addPropType = 0; 
    char addPropAddress[256] = "";
    char addPropCity[128] = "";
    double addPropArea = 0.0;
    int addPropRooms = 0;
    double addPropPrice = 0.0;
    int addPropOwnerID = 0;
    int addPropAgentID = 0;
    string addPropError;

    // Edit Property buffers
    bool showEditPropertyModal = false;
    int editPropID = 0;
    char editPropAddress[256] = "";
    char editPropCity[128] = "";
    double editPropArea = 0.0;
    int editPropRooms = 0;
    double editPropPrice = 0.0;
    int editPropOwnerID = 0;
    int editPropAgentID = 0;
    string editPropError;

    string propListError;
    string clientListError;

    // Add Client buffers
    bool showAddClientModal = false;
    int addClientID = 0;
    char addClientName[128] = "";
    char addClientContact[128] = "";
    int addClientType = 0; // 0: Buyer, 1: Seller, 2: Renter
    string addClientError;

    // Edit Client buffers
    bool showEditClientModal = false;
    int editClientID = 0;
    char editClientName[128] = "";
    char editClientContact[128] = "";
    int editClientType = 0;
    string editClientError;

    // Add Agent buffers
    bool showAddAgentModal = false;
    int addAgentID = 0;
    char addAgentName[128] = "";
    char addAgentContact[128] = "";
    double addAgentComm = 5.0;
    string addAgentError;

    // Edit Agent buffers
    bool showEditAgentModal = false;
    int editAgentID = 0;
    char editAgentName[128] = "";
    char editAgentContact[128] = "";
    double editAgentComm = 5.0;
    string editAgentError;

    // Add Transaction buffers
    bool showAddTransModal = false;
    int addTransID = 0;
    int addContractID = 0;
    int addTransType = 0; // 0: Sale, 1: Rental
    int addTransPropID = 0;
    int addTransClientID = 0;
    int addTransAgentID = 0;
    double addTransAmount = 0.0;
    int addTransDuration = 12; // months
    string addTransError;

    // Add User buffers
    bool showAddUserModal = false;
    char addUserName[128] = "";
    char addUserPass[128] = "";
    int addUserRole = 0; // 0: Admin, 1: Agent, 2: Client
    string addUserError;

    // Change Password buffers
    bool showChangePassModal = false;
    string changePassUsername;
    char changePassNew[128] = "";
    string changePassError;

    // View Details buffers
    bool showViewContractModal = false;
    int viewContractID = 0;
    bool showViewTransModal = false;
    int viewTransID = 0;

public:
    AppGUI(RealEstateAgency& a) : agency(a) {
        agency.loadUsers();
        agency.loadData();
        ApplyStyle();
    }

    void ApplyStyle() {
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 14.0f;
        style.FrameRounding = 10.0f;
        style.PopupRounding = 12.0f;
        style.GrabRounding = 10.0f;
        style.TabRounding = 10.0f;
        style.ChildRounding = 12.0f;
        
        style.WindowPadding = ImVec2(20, 20);
        style.FramePadding = ImVec2(14, 8);
        style.ItemSpacing = ImVec2(14, 12);
        style.CellPadding = ImVec2(10, 10);
        
        style.ScrollbarSize = 12.0f;
        style.ScrollbarRounding = 12.0f;
        style.SeparatorTextBorderSize = 2.0f;

        ImVec4* colors = style.Colors;
        colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg]               = ImVec4(0.02f, 0.02f, 0.05f, 1.00f);
        colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg]                = ImVec4(0.05f, 0.05f, 0.10f, 0.96f);
        colors[ImGuiCol_Border]                 = ImVec4(0.80f, 0.60f, 0.20f, 0.35f); // Luxury Gold
        colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        
        colors[ImGuiCol_FrameBg]                = ImVec4(0.10f, 0.10f, 0.15f, 0.75f);
        colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.15f, 0.15f, 0.25f, 1.00f);
        colors[ImGuiCol_FrameBgActive]          = ImVec4(0.20f, 0.20f, 0.35f, 1.00f);
        
        colors[ImGuiCol_TitleBg]                = ImVec4(0.05f, 0.05f, 0.10f, 1.00f);
        colors[ImGuiCol_TitleBgActive]          = ImVec4(0.10f, 0.08f, 0.15f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        
        colors[ImGuiCol_MenuBarBg]              = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
        colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.05f, 1.00f);
        colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.80f, 0.60f, 0.20f, 0.50f); // Gold Grab
        colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.90f, 0.70f, 0.30f, 0.80f);
        colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(1.00f, 0.80f, 0.40f, 1.00f);
        
        colors[ImGuiCol_CheckMark]              = ImVec4(0.85f, 0.65f, 0.25f, 1.00f); // Gold
        colors[ImGuiCol_SliderGrab]             = ImVec4(0.85f, 0.65f, 0.25f, 1.00f);
        colors[ImGuiCol_SliderGrabActive]       = ImVec4(1.00f, 0.80f, 0.40f, 1.00f);
        
        colors[ImGuiCol_Button]                 = ImVec4(0.15f, 0.15f, 0.30f, 0.80f);
        colors[ImGuiCol_ButtonHovered]          = ImVec4(0.25f, 0.25f, 0.50f, 1.00f);
        colors[ImGuiCol_ButtonActive]           = ImVec4(0.20f, 0.20f, 0.40f, 1.00f);
        
        colors[ImGuiCol_Header]                 = ImVec4(0.80f, 0.60f, 0.20f, 0.25f);
        colors[ImGuiCol_HeaderHovered]          = ImVec4(0.80f, 0.60f, 0.20f, 0.40f);
        colors[ImGuiCol_HeaderActive]           = ImVec4(0.85f, 0.65f, 0.25f, 0.60f);
        
        colors[ImGuiCol_Separator]              = ImVec4(0.80f, 0.60f, 0.20f, 0.30f);
        colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.90f, 0.70f, 0.30f, 0.78f);
        colors[ImGuiCol_SeparatorActive]        = ImVec4(0.90f, 0.70f, 0.30f, 1.00f);
        
        colors[ImGuiCol_ResizeGrip]             = ImVec4(0.80f, 0.60f, 0.20f, 0.20f);
        colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.85f, 0.65f, 0.25f, 0.67f);
        colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.95f, 0.75f, 0.35f, 0.95f);
        
        colors[ImGuiCol_Tab]                    = ImVec4(0.10f, 0.10f, 0.20f, 0.80f);
        colors[ImGuiCol_TabHovered]             = ImVec4(0.80f, 0.60f, 0.20f, 0.80f);
        colors[ImGuiCol_TabActive]              = ImVec4(0.85f, 0.65f, 0.25f, 1.00f);
        colors[ImGuiCol_TabUnfocused]           = ImVec4(0.05f, 0.05f, 0.10f, 0.97f);
        colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.10f, 0.10f, 0.20f, 1.00f);
        
        colors[ImGuiCol_TableRowBg]             = ImVec4(0.05f, 0.05f, 0.10f, 0.40f);
        colors[ImGuiCol_TableRowBgAlt]          = ImVec4(0.08f, 0.08f, 0.15f, 0.50f);
        colors[ImGuiCol_TableBorderLight]       = ImVec4(0.80f, 0.60f, 0.20f, 0.15f);
        colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.80f, 0.60f, 0.20f, 0.30f);
        colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.10f, 0.10f, 0.20f, 0.90f);
    }

    void Render() {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;

        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
        if (ImGui::Begin("MainWindow", nullptr, window_flags)) {
            
            if (loggedIn) {
                // Draw colorful dynamic background
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 wp = ImGui::GetWindowPos();
                ImVec2 ws = ImGui::GetWindowSize();
                double t = ImGui::GetTime();
                
                // 1. Deep Royal Space Base
                draw_list->AddRectFilledMultiColor(wp, ImVec2(wp.x + ws.x, wp.y + ws.y), 
                    IM_COL32(0, 0, 5, 255), IM_COL32(5, 5, 15, 255), 
                    IM_COL32(10, 10, 30, 255), IM_COL32(0, 0, 5, 255));
                
                // 2. Luxurious Silk Nebula Clouds
                auto draw_nebula = [&](ImVec2 pos, float radius, ImU32 col) {
                    for (int i = 0; i < 5; i++) {
                        float r = radius * (1.0f - i * 0.15f);
                        draw_list->AddCircleFilled(pos, r, col & 0x00FFFFFF | (ImU32)(0x04000000 / (i + 1)), 100);
                    }
                };
                draw_nebula(ImVec2(wp.x + ws.x * 0.3f, wp.y + ws.y * 0.3f), 800.0f, IM_COL32(100, 80, 20, 255)); // Gold Mist
                draw_nebula(ImVec2(wp.x + ws.x * 0.7f, wp.y + ws.y * 0.6f), 900.0f, IM_COL32(40, 60, 120, 255)); // Royal Blue Mist
                draw_nebula(ImVec2(wp.x + ws.x * 0.5f, wp.y + ws.y * 0.5f), 500.0f, IM_COL32(200, 180, 150, 255)); // Champagne Mist

                // 3. Cinematic Vignette
                draw_list->AddRectFilledMultiColor(wp, ImVec2(wp.x + ws.x, wp.y + ws.y),
                    IM_COL32(0,0,0,180), IM_COL32(0,0,0,0), IM_COL32(0,0,0,0), IM_COL32(0,0,0,180));

                // 4. Detailed Stardust Field
                for (int i = 0; i < 300; i++) {
                    float seed = (float)i * 1337.0f;
                    float x = (float)fmod(seed, ws.x);
                    float y = (float)fmod(seed * 0.618f, ws.y);
                    float flicker = (float)(sin(t * (1.2 + fmod(seed, 1.5)) + i) * 0.5 + 0.5);
                    ImU32 sCol = (i % 8 == 0) ? IM_COL32(255, 215, 0, (int)(150*flicker)) : IM_COL32(255, 255, 255, (int)(120*flicker));
                    draw_list->AddCircleFilled(ImVec2(wp.x + x, wp.y + y), 0.6f + flicker * 0.6f, sCol);
                }

                // 5. Luxurious Hero Stars with Light Beams (God Rays)
                auto draw_lux_star = [&](ImVec2 pos, float radius, ImU32 col, float p_speed, float m_speed, int n_pts) {
                    float pulse = (float)(sin(t * p_speed) * 0.10 + 1.0);
                    float cur_rad = radius * pulse;
                    ImVec2 mPos = ImVec2(
                        pos.x + (float)cos(t * m_speed) * 50.0f,
                        pos.y + (float)sin(t * m_speed * 0.8) * 50.0f
                    );
                    
                    const float PI = 3.14159265f;
                    
                    // Light Beams (God Rays)
                    for (int b = 0; b < 8; b++) {
                        float b_angle = b * (PI / 4.0f) + (float)t * 0.1f;
                        ImVec2 b_end = ImVec2(mPos.x + (float)cos(b_angle) * cur_rad * 5.0f, mPos.y + (float)sin(b_angle) * cur_rad * 5.0f);
                        draw_list->AddLine(mPos, b_end, col & 0x00FFFFFF | 0x08000000, 2.0f);
                    }

                    // Volumetric Glow Layers
                    for(int g=0; g<5; g++) 
                        draw_list->AddCircleFilled(mPos, cur_rad * (2.2f - g*0.35f), col & 0x00FFFFFF | (ImU32)(0x06000000 * (5-g)), 50);

                    ImVec2 pts[16];
                    int ptCount = 2 * n_pts;
                    float aStep = PI / n_pts;
                    float iRad = cur_rad * 0.38f;
                    
                    for (int i = 0; i < ptCount; i++) {
                        float r = (i % 2 == 0) ? cur_rad : iRad;
                        float angle = i * aStep - PI/2.0f + (float)t * (0.2f + m_speed*0.04f);
                        pts[i] = ImVec2(mPos.x + r * (float)cos(angle), mPos.y + r * (float)sin(angle));
                    }
                    draw_list->AddConvexPolyFilled(pts, ptCount, col);
                    draw_list->AddCircleFilled(mPos, cur_rad * 0.12f, IM_COL32(255, 255, 255, 240));
                };

                draw_lux_star(ImVec2(wp.x + ws.x * 0.85f, wp.y + ws.y * 0.2f), 120.0f, IM_COL32(255, 215, 0, 40), 0.5f, 0.15f, 5); // Gold
                draw_lux_star(ImVec2(wp.x + ws.x * 0.15f, wp.y + ws.y * 0.85f), 150.0f, IM_COL32(200, 220, 255, 45), 0.6f, 0.12f, 6); // Diamond Blue
                draw_lux_star(ImVec2(wp.x + ws.x * 0.55f, wp.y + ws.y * 0.5f), 100.0f,  IM_COL32(255, 255, 255, 35), 0.8f, 0.20f, 5); // Pure White
                draw_lux_star(ImVec2(wp.x + ws.x * 0.30f, wp.y + ws.y * 0.2f), 80.0f,   IM_COL32(255, 200, 100, 40), 0.4f, 0.18f, 4); // Champagne
                draw_lux_star(ImVec2(wp.x + ws.x * 0.90f, wp.y + ws.y * 0.9f), 60.0f,   IM_COL32(255, 215, 0, 40), 1.1f, 0.30f, 5); // Gold
            }

            if (!loggedIn) {
                RenderLogin();
            } else {
                RenderMenuBar();
                RenderCurrentView();
            }
        }
        ImGui::End();
        ImGui::PopStyleColor();

        RenderModals();
    }

private:
    void RenderLogin() {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetWindowPos();
        ImVec2 size = ImGui::GetWindowSize();
        
        // 1. Artistic Cityscape Background
        // Sky Gradient (Sunset/Dawn)
        draw_list->AddRectFilledMultiColor(p, ImVec2(p.x + size.x, p.y + size.y), 
            IM_COL32(25, 20, 50, 255), IM_COL32(25, 20, 50, 255), 
            IM_COL32(120, 50, 80, 255), IM_COL32(120, 50, 80, 255));

        // Sun / Moon with Glow
        draw_list->AddCircleFilled(ImVec2(p.x + size.x * 0.75f, p.y + size.y * 0.25f), 100.0f, IM_COL32(255, 120, 80, 180), 64);
        draw_list->AddCircleFilled(ImVec2(p.x + size.x * 0.75f, p.y + size.y * 0.25f), 120.0f, IM_COL32(255, 120, 80, 40), 64);

        float base_y = p.y + size.y;
        
        // Background Mountains / Hills
        draw_list->AddTriangleFilled(ImVec2(p.x - 100, base_y), ImVec2(p.x + 400, base_y - 250), ImVec2(p.x + 900, base_y), IM_COL32(40, 20, 60, 150));
        draw_list->AddTriangleFilled(ImVec2(p.x + size.x * 0.3f, base_y), ImVec2(p.x + size.x * 0.7f, base_y - 350), ImVec2(p.x + size.x + 200, base_y), IM_COL32(30, 15, 50, 180));

        // Colorful Real Estate Buildings
        // Building 1 (Cyan/Blue)
        draw_list->AddRectFilled(ImVec2(p.x + size.x * 0.1f, base_y - 350), ImVec2(p.x + size.x * 0.22f, base_y), IM_COL32(20, 120, 180, 230), 5.0f);
        for(int i=0; i<6; i++) {
            for(int j=0; j<3; j++) {
                draw_list->AddRectFilled(ImVec2(p.x + size.x * 0.1f + 15 + j*35, base_y - 330 + i*55), ImVec2(p.x + size.x * 0.1f + 35 + j*35, base_y - 300 + i*55), IM_COL32(255, 240, 150, 200), 2.0f);
            }
        }

        // Building 2 (Purple/Pink - Main Tower)
        draw_list->AddRectFilled(ImVec2(p.x + size.x * 0.25f, base_y - 500), ImVec2(p.x + size.x * 0.4f, base_y), IM_COL32(110, 40, 150, 240), 8.0f);
        draw_list->AddTriangleFilled(ImVec2(p.x + size.x * 0.25f, base_y - 500), ImVec2(p.x + size.x * 0.4f, base_y - 500), ImVec2(p.x + size.x * 0.325f, base_y - 580), IM_COL32(110, 40, 150, 240));
        for(int i=0; i<10; i++) {
            draw_list->AddRectFilled(ImVec2(p.x + size.x * 0.25f + 20, base_y - 480 + i*45), ImVec2(p.x + size.x * 0.4f - 20, base_y - 460 + i*45), IM_COL32(150, 200, 255, 180), 3.0f);
        }

        // Building 3 (Orange/Red - Modern Villa)
        draw_list->AddRectFilled(ImVec2(p.x + size.x * 0.65f, base_y - 250), ImVec2(p.x + size.x * 0.85f, base_y), IM_COL32(200, 70, 40, 230), 6.0f);
        draw_list->AddRectFilled(ImVec2(p.x + size.x * 0.65f - 20, base_y - 260), ImVec2(p.x + size.x * 0.85f + 20, base_y - 240), IM_COL32(150, 40, 20, 255), 4.0f);
        for(int j=0; j<2; j++) {
            draw_list->AddRectFilled(ImVec2(p.x + size.x * 0.65f + 30 + j*80, base_y - 180), ImVec2(p.x + size.x * 0.65f + 90 + j*80, base_y - 80), IM_COL32(200, 240, 255, 200));
        }

        // Ground / Road
        draw_list->AddRectFilled(ImVec2(p.x, base_y - 40), ImVec2(p.x + size.x, base_y), IM_COL32(25, 25, 30, 255));
        for(float x = 20; x < size.x; x += 80) {
            draw_list->AddRectFilled(ImVec2(p.x + x, base_y - 25), ImVec2(p.x + x + 40, base_y - 15), IM_COL32(200, 180, 50, 200));
        }

        // trees
        draw_list->AddCircleFilled(ImVec2(p.x + size.x * 0.23f, base_y - 70), 50.0f, IM_COL32(40, 180, 80, 220), 32);
        draw_list->AddCircleFilled(ImVec2(p.x + size.x * 0.43f, base_y - 60), 40.0f, IM_COL32(30, 150, 60, 220), 32);
        draw_list->AddCircleFilled(ImVec2(p.x + size.x * 0.60f, base_y - 80), 60.0f, IM_COL32(50, 200, 90, 220), 32);

        // 2. Original Semi-transparent Login Box
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.06f, 0.05f, 0.12f, 0.85f));
        ImGui::SetCursorPos(ImVec2(size.x * 0.5f - 175, size.y * 0.5f - 145));
        if (ImGui::BeginChild("LoginBox", ImVec2(350, 290), true, ImGuiWindowFlags_NoScrollbar)) {
            
            ImGui::Spacing();
            ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize("REAL ESTATE AGENCY").x) * 0.5f);
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.8f, 1.0f), "REAL ESTATE AGENCY");
            
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::Text("Username");
            ImGui::SetNextItemWidth(-1);
            ImGui::InputText("##User", loginUser, IM_ARRAYSIZE(loginUser));
            
            ImGui::Spacing();
            ImGui::Text("Password");
            ImGui::SetNextItemWidth(-1);
            ImGui::InputText("##Pass", loginPass, IM_ARRAYSIZE(loginPass), ImGuiInputTextFlags_Password);
            
            if (!loginError.empty()) {
                ImGui::Spacing();
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - ImGui::CalcTextSize(loginError.c_str()).x) * 0.5f);
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "%s", loginError.c_str());
            }

            // Anchor the button beautifully to the bottom
            ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 55);
            
            if (ImGui::Button("LOGIN", ImVec2(ImGui::GetContentRegionAvail().x, 40))) {
                if (agency.authenticate(loginUser, loginPass, currentRole)) {
                    loggedIn = true;
                    currentUsername = loginUser;
                    currentView = View::Properties;
                    loginError = "";
                } else {
                    loginError = "Invalid username or password.";
                }
            }
        }
        ImGui::EndChild();
        ImGui::PopStyleColor();
    }

    void RenderMenuBar() {
        if (ImGui::BeginMenuBar()) {
            if (ImGui::MenuItem("Properties", nullptr, currentView == View::Properties)) currentView = View::Properties;
            if (currentRole == UserRole::ADMIN || currentRole == UserRole::AGENT) {
                if (ImGui::MenuItem("Clients", nullptr, currentView == View::Clients)) currentView = View::Clients;
                if (ImGui::MenuItem("Agents", nullptr, currentView == View::Agents)) currentView = View::Agents;
                if (ImGui::MenuItem("Transactions", nullptr, currentView == View::Transactions)) currentView = View::Transactions;
                if (ImGui::MenuItem("Contracts", nullptr, currentView == View::Contracts)) currentView = View::Contracts;
                if (ImGui::MenuItem("Reports", nullptr, currentView == View::Reports)) currentView = View::Reports;
            }
            if (currentRole == UserRole::ADMIN) {
                if (ImGui::MenuItem("Users", nullptr, currentView == View::Users)) currentView = View::Users;
            }

            ImGui::Separator();
            if (ImGui::MenuItem("Save Data")) {
                agency.saveData();
            }
            if (ImGui::MenuItem("Load Data")) {
                agency.loadData();
            }

            ImGui::Separator();
            ImGui::TextDisabled("User: %s (%s)", currentUsername.c_str(), roleToString(currentRole).c_str());

            if (ImGui::MenuItem("Logout")) {
                loggedIn = false;
                loginUser[0] = '\0';
                loginPass[0] = '\0';
            }
            ImGui::EndMenuBar();
        }
    }

    void RenderCurrentView() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));
        ImGui::BeginChild("ViewArea", ImVec2(0, 0), false);
        switch (currentView) {
            case View::Properties: RenderProperties(); break;
            case View::Clients: RenderClients(); break;
            case View::Agents: RenderAgents(); break;
            case View::Transactions: RenderTransactions(); break;
            case View::Contracts: RenderContracts(); break;
            case View::Users: RenderUsers(); break;
            case View::Reports: RenderReports(); break;
            default: break;
        }
        ImGui::EndChild();
        ImGui::PopStyleVar();
    }

    void RenderProperties() {
        ImGui::SetWindowFontScale(1.2f);
        ImGui::Text("Properties Management");
        ImGui::SetWindowFontScale(1.0f);
        ImGui::Separator();
        ImGui::Spacing();

        // Search and Add
        ImGui::SetNextItemWidth(300);
        ImGui::InputTextWithHint("##PropSearch", "Search properties by city or address...", propSearch, IM_ARRAYSIZE(propSearch));
        
        ImGui::SameLine();
        if (ImGui::Button(showAdvancedSearch ? "Hide Filters" : "Advanced Filters")) {
            showAdvancedSearch = !showAdvancedSearch;
        }

        if (currentRole == UserRole::ADMIN || currentRole == UserRole::AGENT) {
            ImGui::SameLine(ImGui::GetWindowWidth() - 140);
            if (ImGui::Button("Add Property", ImVec2(120, 0))) {
                showAddPropertyModal = true;
                addPropError = "";
            }
        }

        if (showAdvancedSearch) {
            ImGui::Spacing();
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.08f, 0.20f, 0.6f));
            if (ImGui::BeginChild("AdvancedSearchPanel", ImVec2(0, 50), true)) {
                ImGui::SetNextItemWidth(100);
                ImGui::InputDouble("Min Price", &searchMinPrice, 0, 0, "%.0f");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(100);
                ImGui::InputDouble("Max Price", &searchMaxPrice, 0, 0, "%.0f");
                
                ImGui::SameLine();
                const char* types[] = { "Any", "Apartment", "Villa", "Office", "Land" };
                ImGui::SetNextItemWidth(120);
                ImGui::Combo("Type", &searchType, types, IM_ARRAYSIZE(types));
                
                ImGui::SameLine();
                const char* statuses[] = { "Any", "Available", "Sold", "Rented" };
                ImGui::SetNextItemWidth(120);
                ImGui::Combo("Status", &searchStatus, statuses, IM_ARRAYSIZE(statuses));
            }
            ImGui::EndChild();
            ImGui::PopStyleColor();
        }

        ImGui::Spacing();

        if (ImGui::BeginTable("PropertiesTable", 9, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY)) {
            ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 40);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 100);
            ImGui::TableSetupColumn("City", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Address", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Area", ImGuiTableColumnFlags_WidthFixed, 80);
            ImGui::TableSetupColumn("Rooms", ImGuiTableColumnFlags_WidthFixed, 50);
            ImGui::TableSetupColumn("Price", ImGuiTableColumnFlags_WidthFixed, 100);
            ImGui::TableSetupColumn("Status", ImGuiTableColumnFlags_WidthFixed, 110);
            ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_WidthFixed, 150);
            ImGui::TableHeadersRow();

            if (!propListError.empty()) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(255, 0, 0, 40));
                ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "Error: %s", propListError.c_str());
                ImGui::SameLine();
                if (ImGui::Button("Clear Error")) propListError = "";
                // Fill remaining columns
                for (int i = 0; i < 8; ++i) ImGui::TableNextColumn();
            }

            string searchStr = toLower(propSearch);

            for (size_t i = 0; i < agency.properties.size(); ) {
                auto& prop = agency.properties[i];
                
                // --- Filtering Logic ---
                if (!searchStr.empty()) {
                    if (toLower(prop->getCity()).find(searchStr) == string::npos &&
                        toLower(prop->getAddress()).find(searchStr) == string::npos) {
                        i++;
                        continue;
                    }
                }
                if (showAdvancedSearch) {
                    if (searchMinPrice > 0 && prop->getPrice() < searchMinPrice) { i++; continue; }
                    if (searchMaxPrice > 0 && prop->getPrice() > searchMaxPrice) { i++; continue; }
                    if (searchType > 0 && static_cast<int>(prop->getType()) != (searchType - 1)) { i++; continue; }
                    if (searchStatus > 0 && static_cast<int>(prop->getStatus()) != (searchStatus - 1)) { i++; continue; }
                }

                ImGui::PushID(prop->getID());
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); ImGui::Text("%d", prop->getID());
                ImGui::TableSetColumnIndex(1); ImGui::Text("%s", prop->getPropertyTypeStr().c_str());
                ImGui::TableSetColumnIndex(2); ImGui::Text("%s", prop->getCity().c_str());
                ImGui::TableSetColumnIndex(3); ImGui::Text("%s", prop->getAddress().c_str());
                ImGui::TableSetColumnIndex(4); ImGui::Text("%.1f", prop->getArea());
                ImGui::TableSetColumnIndex(5); ImGui::Text("%d", prop->getRooms());
                ImGui::TableSetColumnIndex(6); ImGui::Text("$%.0f", prop->getPrice());
                
                ImGui::TableSetColumnIndex(7); 
                PropertyStatus st = prop->getStatus();
                ImVec4 badgeColor;
                string stText;
                if (st == PropertyStatus::AVAILABLE) { badgeColor = ImVec4(0.1f, 0.7f, 0.3f, 1.0f); stText = "Available"; }
                else if (st == PropertyStatus::SOLD) { badgeColor = ImVec4(0.8f, 0.2f, 0.2f, 1.0f); stText = "Sold"; }
                else { badgeColor = ImVec4(0.8f, 0.6f, 0.1f, 1.0f); stText = "Rented"; }

                ImGui::PushStyleColor(ImGuiCol_Button, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, badgeColor);
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
                ImGui::Button(stText.c_str(), ImVec2(90, 0));
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);
                
                ImGui::TableSetColumnIndex(8); 
                bool removed = false;
                if (currentRole == UserRole::ADMIN || currentRole == UserRole::AGENT) {
                    if (ImGui::Button("Edit")) {
                        showEditPropertyModal = true;
                        editPropID = prop->getID();
                        strcpy_s(editPropAddress, prop->getAddress().c_str());
                        strcpy_s(editPropCity, prop->getCity().c_str());
                        editPropArea = prop->getArea();
                        editPropRooms = prop->getRooms();
                        editPropPrice = prop->getPrice();
                        editPropOwnerID = prop->getOwnerID();
                        editPropAgentID = prop->getAgentID();
                        editPropError = "";
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Remove")) {
                        if (agency.removePropertyGUI(prop->getID(), propListError)) {
                            propListError = "";
                            removed = true;
                        }
                    }
                } else {
                    ImGui::TextDisabled("-");
                }
                ImGui::PopID();
                if (removed) continue;
                i++;
            }
            ImGui::EndTable();
        }
    }

    void RenderClients() {
        ImGui::Text("Clients Management");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SetNextItemWidth(300);
        ImGui::InputTextWithHint("##ClientSearch", "Search clients by name...", clientSearch, IM_ARRAYSIZE(clientSearch));
        
        if (currentRole == UserRole::ADMIN || currentRole == UserRole::AGENT) {
            ImGui::SameLine(ImGui::GetWindowWidth() - 140);
            if (ImGui::Button("Add Client", ImVec2(120, 0))) {
                showAddClientModal = true;
            }
        }
        ImGui::Spacing();

        if (ImGui::BeginTable("ClientsTable", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY)) {
            ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 40);
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Contact", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 100);
            ImGui::TableSetupColumn("Trans.", ImGuiTableColumnFlags_WidthFixed, 60);
            ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_WidthFixed, 140);
            ImGui::TableHeadersRow();

            if (!clientListError.empty()) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, IM_COL32(255, 0, 0, 40));
                ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), "Error: %s", clientListError.c_str());
                ImGui::SameLine();
                if (ImGui::Button("Clear Error")) clientListError = "";
                // Fill remaining columns
                for (int i = 0; i < 5; ++i) ImGui::TableNextColumn();
            }

            string searchStr = toLower(clientSearch);

            for (size_t i = 0; i < agency.clients.size(); ) {
                auto& client = agency.clients[i];
                if (!searchStr.empty() && toLower(client->getName()).find(searchStr) == string::npos) { i++; continue; }

                ImGui::PushID(client->getID());
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); ImGui::Text("%d", client->getID());
                ImGui::TableSetColumnIndex(1); ImGui::Text("%s", client->getName().c_str());
                ImGui::TableSetColumnIndex(2); ImGui::Text("%s", client->getContactInfo().c_str());
                
                ImGui::TableSetColumnIndex(3); 
                // Perfect badges for Client Type
                string typeStr = clientTypeToString(client->getType());
                ImVec4 badgeColor;
                if (client->getType() == ClientType::BUYER) badgeColor = ImVec4(0.0f, 0.7f, 1.0f, 1.0f);      // Cyan
                else if (client->getType() == ClientType::SELLER) badgeColor = ImVec4(1.0f, 0.4f, 0.0f, 1.0f); // Orange
                else badgeColor = ImVec4(1.0f, 0.8f, 0.0f, 1.0f);                                           // Gold/Yellow

                ImGui::PushStyleColor(ImGuiCol_Button, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, badgeColor);
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
                ImGui::Button(typeStr.c_str(), ImVec2(80, 0));
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);

                ImGui::TableSetColumnIndex(4); ImGui::Text("%zu", client->getTransactionHistory().size());
                
                ImGui::TableSetColumnIndex(5);
                bool removed = false;
                if (currentRole == UserRole::ADMIN || currentRole == UserRole::AGENT) {
                    if (ImGui::Button("Edit")) {
                        editClientID = client->getID();
                        strcpy_s(editClientName, client->getName().c_str());
                        strcpy_s(editClientContact, client->getContactInfo().c_str());
                        editClientType = (int)client->getType();
                        showEditClientModal = true;
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("Remove")) {
                        string err;
                        if (agency.removeClientGUI(client->getID(), err)) {
                            clientListError = "";
                            removed = true;
                        } else {
                            clientListError = err;
                        }
                    }
                } else {
                    ImGui::TextDisabled("-");
                }
                ImGui::PopID();

                if (removed) continue;
                i++;
            }
            ImGui::EndTable();
        }
    }

    void RenderAgents() {
        ImGui::Text("Agents Management");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SetNextItemWidth(300);
        ImGui::InputTextWithHint("##AgentSearch", "Search agents by name...", agentSearch, IM_ARRAYSIZE(agentSearch));
        
        if (currentRole == UserRole::ADMIN) {
            ImGui::SameLine(ImGui::GetWindowWidth() - 140);
            if (ImGui::Button("Add Agent", ImVec2(120, 0))) {
                showAddAgentModal = true;
            }
        }
        ImGui::Spacing();

        if (ImGui::BeginTable("AgentsTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY)) {
            ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 40.0f);
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Contact", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Comm %", ImGuiTableColumnFlags_WidthFixed, 80.0f);
            ImGui::TableSetupColumn("Actions", ImGuiTableColumnFlags_WidthFixed, 140.0f);
            ImGui::TableHeadersRow();

            string searchStr = toLower(agentSearch);

            for (size_t i = 0; i < agency.agents.size(); ) {
                auto& agent = agency.agents[i];
                if (!searchStr.empty() && toLower(agent->getName()).find(searchStr) == string::npos) { i++; continue; }

                ImGui::PushID(agent->getID());
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); ImGui::Text("%d", agent->getID());
                ImGui::TableSetColumnIndex(1); ImGui::Text("%s", agent->getName().c_str());
                ImGui::TableSetColumnIndex(2); ImGui::Text("%s", agent->getContactInfo().c_str());
                
                ImGui::TableSetColumnIndex(3);
                float comm = (float)agent->getCommissionRate();
                ImVec4 commColor = ImVec4(0.0f, 1.0f, 0.7f, 1.0f);
                if (comm > 5.0f) commColor = ImVec4(0.0f, 1.0f, 0.5f, 1.0f);
                ImGui::TextColored(commColor, "%.1f%%", comm);

                ImGui::TableSetColumnIndex(4);
                bool removed = false;
                if (ImGui::Button("Edit")) {
                    editAgentID = agent->getID();
                    strcpy_s(editAgentName, agent->getName().c_str());
                    strcpy_s(editAgentContact, agent->getContactInfo().c_str());
                    editAgentComm = agent->getCommissionRate();
                    showEditAgentModal = true;
                    editAgentError = "";
                }
                ImGui::SameLine();
                if (ImGui::Button("Remove")) {
                    string err;
                    if (agency.removeAgentGUI(agent->getID(), err)) {
                        clientListError = "";
                        removed = true;
                    } else {
                        clientListError = err;
                    }
                }
                ImGui::PopID();

                if (removed) continue;
                i++;
            }
            ImGui::EndTable();
        }
    }

    void RenderTransactions() {
        ImGui::Text("Transactions Ledger");
        ImGui::Separator();
        ImGui::Spacing();

        if (currentRole == UserRole::ADMIN || currentRole == UserRole::AGENT) {
            if (ImGui::Button("Record New Transaction", ImVec2(200, 0))) {
                showAddTransModal = true;
                addTransError = "";
            }
        }
        ImGui::Spacing();

        if (ImGui::BeginTable("TransactionsTable", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY)) {
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 100);
            ImGui::TableSetupColumn("Property", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Buyer/Renter", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Amount", ImGuiTableColumnFlags_WidthFixed, 100);
            ImGui::TableSetupColumn("Comm.", ImGuiTableColumnFlags_WidthFixed, 80);
            ImGui::TableSetupColumn("Date", ImGuiTableColumnFlags_WidthFixed, 100);
            ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_WidthFixed, 80);
            ImGui::TableHeadersRow();

            for (auto& trans : agency.transactions) {
                ImGui::PushID(trans->getID());
                ImGui::TableNextRow();
                
                ImGui::TableSetColumnIndex(0);
                string typeStr = (trans->getType() == TransactionType::SALE ? "Sale" : "Rental");
                ImVec4 badgeColor = (trans->getType() == TransactionType::SALE ? ImVec4(0.1f, 0.8f, 0.3f, 1.0f) : ImVec4(0.0f, 0.6f, 0.9f, 1.0f));
                
                ImGui::PushStyleColor(ImGuiCol_Button, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, badgeColor);
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
                ImGui::Button(typeStr.c_str(), ImVec2(80, 0));
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);

                auto pIt = agency.propertyMap.find(trans->getPropertyID());
                ImGui::TableSetColumnIndex(1); ImGui::Text("%s", pIt != agency.propertyMap.end() ? pIt->second->getAddress().c_str() : "Unknown");
                
                auto cIt = agency.clientMap.find(trans->getClientID());
                ImGui::TableSetColumnIndex(2); ImGui::Text("%s", cIt != agency.clientMap.end() ? cIt->second->getName().c_str() : "Unknown");
                
                ImGui::TableSetColumnIndex(3); 
                ImGui::TextColored(badgeColor, "$%.2f", trans->getAmount());
                
                ImGui::TableSetColumnIndex(4); ImGui::Text("$%.2f", trans->getCommission());
                ImGui::TableSetColumnIndex(5); ImGui::Text("%s", trans->getDate().c_str());

                ImGui::TableSetColumnIndex(6);
                if (ImGui::Button("View")) {
                    viewTransID = trans->getID();
                    showViewTransModal = true;
                }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
    }

    void RenderContracts() {
        ImGui::Text("Legal Contracts & Documentation");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::SetNextItemWidth(300);
        ImGui::InputTextWithHint("##ContractSearch", "Search by ID, Type or Client...", contractSearch, IM_ARRAYSIZE(contractSearch));
        ImGui::Spacing();

        if (ImGui::BeginTable("ContractsTable", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY)) {
            ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 40);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, 150);
            ImGui::TableSetupColumn("Property", ImGuiTableColumnFlags_WidthFixed, 80);
            ImGui::TableSetupColumn("Client", ImGuiTableColumnFlags_WidthFixed, 80);
            ImGui::TableSetupColumn("Amount", ImGuiTableColumnFlags_WidthFixed, 100);
            ImGui::TableSetupColumn("Date", ImGuiTableColumnFlags_WidthFixed, 100);
            ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_WidthFixed, 80);
            ImGui::TableHeadersRow();

            string searchStr = toLower(contractSearch);

            for (auto& contract : agency.contracts) {
                if (!searchStr.empty()) {
                    string idStr = to_string(contract->getID());
                    string typeStrLow = toLower(contract->getContractType());
                    
                    bool match = false;
                    if (idStr.find(searchStr) != string::npos) match = true;
                    if (typeStrLow.find(searchStr) != string::npos) match = true;
                    
                    auto cIt = agency.clientMap.find(contract->getClientID());
                    if (cIt != agency.clientMap.end()) {
                        if (toLower(cIt->second->getName()).find(searchStr) != string::npos) match = true;
                    }
                    
                    if (!match) continue;
                }

                ImGui::PushID(contract->getID());
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); ImGui::Text("%d", contract->getID());
                
                ImGui::TableSetColumnIndex(1);
                // Contract Type Badges
                string typeStr = contract->getContractType();
                ImVec4 badgeColor = ImVec4(0.6f, 0.3f, 0.9f, 1.0f); // Purple
                if (typeStr.find("Sale") != string::npos) badgeColor = ImVec4(0.2f, 0.7f, 0.4f, 1.0f); // Greenish
                
                ImGui::PushStyleColor(ImGuiCol_Button, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, badgeColor);
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
                ImGui::Button(typeStr.c_str(), ImVec2(130, 0));
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);

                ImGui::TableSetColumnIndex(2); ImGui::Text("Prop %d", contract->getPropertyID());
                ImGui::TableSetColumnIndex(3); ImGui::Text("Client %d", contract->getClientID());
                ImGui::TableSetColumnIndex(4); ImGui::Text("$%.2f", contract->getAmount());
                ImGui::TableSetColumnIndex(5); ImGui::Text("%s", contract->getDate().c_str());

                ImGui::TableSetColumnIndex(6);
                if (ImGui::Button("View")) {
                    viewContractID = contract->getID();
                    showViewContractModal = true;
                }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
    }

    void RenderReports() {
        ImGui::Text("Agency Performance & Analytics");
        ImGui::Separator();
        ImGui::Spacing();

        auto stats = ReportGenerator::generateStats(agency);

        // Summary Cards
        ImGui::Columns(5, "StatsColumns", false);
        
        auto draw_stat_card = [&](const char* label, const char* value, ImVec4 color) {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(color.x, color.y, color.z, 0.15f));
            ImGui::BeginChild(label, ImVec2(0, 100), true);
            ImGui::TextDisabled("%s", label);
            ImGui::SetWindowFontScale(2.0f);
            ImGui::TextColored(color, "%s", value);
            ImGui::SetWindowFontScale(1.0f);
            ImGui::EndChild();
            ImGui::PopStyleColor();
            ImGui::NextColumn();
        };

        draw_stat_card("Total Properties", to_string(stats.totalProperties).c_str(), ImVec4(0.0f, 0.8f, 1.0f, 1.0f));
        draw_stat_card("Sold Properties", to_string(stats.soldProperties).c_str(), ImVec4(0.0f, 1.0f, 0.5f, 1.0f));
        draw_stat_card("Rented Properties", to_string(stats.rentedProperties).c_str(), ImVec4(0.0f, 0.8f, 0.8f, 1.0f));
        draw_stat_card("Agency Profit", ("$" + to_string((int)stats.totalProfit)).c_str(), ImVec4(1.0f, 0.8f, 0.0f, 1.0f));
        draw_stat_card("Active Listings", to_string(stats.availableProperties).c_str(), ImVec4(0.8f, 0.4f, 1.0f, 1.0f));

        ImGui::Columns(1);
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Agent Performance Ranking");
        if (ImGui::BeginTable("AgentRankTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("Agent", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Deals", ImGuiTableColumnFlags_WidthFixed, 80);
            ImGui::TableSetupColumn("Total Volume", ImGuiTableColumnFlags_WidthFixed, 150);
            ImGui::TableSetupColumn("Ranking", ImGuiTableColumnFlags_WidthFixed, 100);
            ImGui::TableHeadersRow();

            // Sort agents by sales volume
            struct RankItem { int id; string name; int deals; double volume; };
            vector<RankItem> rankings;
            for (const auto& agent : agency.agents) {
                rankings.push_back({ agent->getID(), agent->getName(), stats.agentDealCount[agent->getID()], stats.agentSales[agent->getID()] });
            }
            sort(rankings.begin(), rankings.end(), [](const RankItem& a, const RankItem& b) {
                return a.volume > b.volume;
            });

            for (size_t i = 0; i < rankings.size(); i++) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); ImGui::Text("%s", rankings[i].name.c_str());
                ImGui::TableSetColumnIndex(1); ImGui::Text("%d", rankings[i].deals);
                ImGui::TableSetColumnIndex(2); ImGui::Text("$%.2f", rankings[i].volume);
                ImGui::TableSetColumnIndex(3);
                if (i == 0) ImGui::TextColored(ImVec4(1, 0.8f, 0, 1), "GOLD");
                else if (i == 1) ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1), "SILVER");
                else if (i == 2) ImGui::TextColored(ImVec4(0.8f, 0.5f, 0.2f, 1), "BRONZE");
                else ImGui::Text("#%zu", i + 1);
            }
            ImGui::EndTable();
        }
    }

    void RenderUsers() {
        ImGui::Text("System User Access Control");
        ImGui::Separator();
        ImGui::Spacing();

        if (currentRole == UserRole::ADMIN) {
            ImGui::SameLine(ImGui::GetWindowWidth() - 140);
            
            // Add User button with Success color (Greenish)
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.6f, 0.4f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.7f, 0.5f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.5f, 0.3f, 1.0f));
            if (ImGui::Button("Add User", ImVec2(120, 0))) {
                showAddUserModal = true;
                addUserError = "";
            }
            ImGui::PopStyleColor(3);
        }
        ImGui::Spacing();

        if (ImGui::BeginTable("UsersTable", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY)) {
            ImGui::TableSetupColumn("Username", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Role", ImGuiTableColumnFlags_WidthFixed, 120);
            ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_WidthFixed, 240);
            ImGui::TableHeadersRow();

            for (auto it = agency.users.begin(); it != agency.users.end(); ) {
                auto& uname = it->first;
                auto& user = it->second;

                ImGui::PushID(uname.c_str());
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0); 
                ImGui::Text("%s", uname.c_str());
                if (uname == "admin") {
                    ImGui::SameLine();
                    ImGui::TextDisabled("(System)");
                }
                
                ImGui::TableSetColumnIndex(1);
                // User Role Badges
                string roleStr = roleToString(user.getRole());
                ImVec4 badgeColor;
                if (user.getRole() == UserRole::ADMIN) badgeColor = ImVec4(1.0f, 0.2f, 0.2f, 1.0f);    // Red
                else if (user.getRole() == UserRole::AGENT) badgeColor = ImVec4(0.0f, 0.8f, 0.8f, 1.0f); // Teal
                else badgeColor = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);                                     // Grey

                ImGui::PushStyleColor(ImGuiCol_Button, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, badgeColor);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, badgeColor);
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
                ImGui::Button(roleStr.c_str(), ImVec2(80, 0));
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);

                ImGui::TableSetColumnIndex(2);
                bool erased = false;
                if (currentRole == UserRole::ADMIN) {
                    // Change Password with Info color (Blueish)
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.4f, 0.8f, 0.8f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.5f, 0.9f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.4f, 0.7f, 1.0f));
                    if (ImGui::Button("Change Password")) {
                        showChangePassModal = true;
                        changePassUsername = uname;
                        changePassError = "";
                        changePassNew[0] = '\0';
                    }
                    ImGui::PopStyleColor(3);

                    ImGui::SameLine();
                    if (uname != "admin") {
                        // Remove with Danger color (Reddish)
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.1f, 0.1f, 0.8f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.1f, 0.1f, 1.0f));
                        if (ImGui::Button("Remove")) {
                            it = agency.users.erase(it);
                            agency.saveUsers();
                            erased = true;
                        }
                        if (!erased) ImGui::PopStyleColor(3);
                    } else {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 0.4f));
                        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 12.0f);
                        ImGui::Button("Fixed", ImVec2(70, 0));
                        ImGui::PopStyleVar();
                        ImGui::PopStyleColor();
                    }
                } else {
                    ImGui::TextDisabled("-");
                }
                ImGui::PopID();
                if (erased) continue;
                ++it;
            }
            ImGui::EndTable();
        }
    }

    void RenderModals() {
        // --- Add Property Modal ---
        if (showAddPropertyModal) ImGui::OpenPopup("Add Property ##Modal");
        if (ImGui::BeginPopupModal("Add Property ##Modal", &showAddPropertyModal, ImGuiWindowFlags_AlwaysAutoResize)) {
            const char* types[] = { "Apartment", "Villa", "Office", "Land" };
            ImGui::Combo("Type", &addPropType, types, IM_ARRAYSIZE(types));
            ImGui::InputText("Address", addPropAddress, IM_ARRAYSIZE(addPropAddress));
            ImGui::InputText("City", addPropCity, IM_ARRAYSIZE(addPropCity));
            ImGui::InputDouble("Area (sqm)", &addPropArea);
            if (addPropType != 3) ImGui::InputInt("Rooms", &addPropRooms);
            ImGui::InputDouble("Price", &addPropPrice);
            ImGui::InputInt("Owner Client ID", &addPropOwnerID);
            ImGui::InputInt("Agent ID (Optional)", &addPropAgentID);

            if (!addPropError.empty()) ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", addPropError.c_str());

            ImGui::Separator();
            if (ImGui::Button("Confirm", ImVec2(120, 0))) {
                if (agency.addPropertyGUI(addPropID, static_cast<PropertyType>(addPropType), addPropAddress, addPropCity, addPropArea, addPropRooms, addPropPrice, addPropOwnerID, addPropAgentID, addPropError)) {
                    showAddPropertyModal = false;
                    addPropID = 0;
                    addPropAddress[0] = '\0'; addPropCity[0] = '\0'; addPropArea = 0; addPropRooms = 0; addPropPrice = 0;
                    addPropOwnerID = 0; addPropAgentID = 0; addPropError = "";
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) showAddPropertyModal = false;
            ImGui::EndPopup();
        }

        // --- Edit Property Modal ---
        if (showEditPropertyModal) ImGui::OpenPopup("Edit Property ##Modal");
        if (ImGui::BeginPopupModal("Edit Property ##Modal", &showEditPropertyModal, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Editing Property ID: %d", editPropID);
            ImGui::InputText("Address", editPropAddress, IM_ARRAYSIZE(editPropAddress));
            ImGui::InputText("City", editPropCity, IM_ARRAYSIZE(editPropCity));
            ImGui::InputDouble("Area (sqm)", &editPropArea);
            ImGui::InputInt("Rooms", &editPropRooms);
            ImGui::InputDouble("Price ($)", &editPropPrice);
            ImGui::InputInt("Owner ID", &editPropOwnerID);
            ImGui::InputInt("Agent ID (0 if none)", &editPropAgentID);

            if (!editPropError.empty()) ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "%s", editPropError.c_str());

            ImGui::Separator();
            if (ImGui::Button("Confirm", ImVec2(120, 0))) {
                if (agency.editPropertyGUI(editPropID, editPropAddress, editPropCity, editPropArea, editPropRooms, editPropPrice, editPropOwnerID, editPropError)) {
                    // Update listing agent relationship
                    agency.assignAgentGUI(editPropID, editPropAgentID, editPropError);
                    showEditPropertyModal = false;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) showEditPropertyModal = false;
            ImGui::EndPopup();
        }

        // --- Add Client Modal ---
        if (showAddClientModal) ImGui::OpenPopup("Add Client ##Modal");
        if (ImGui::BeginPopupModal("Add Client ##Modal", &showAddClientModal, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::InputText("Name", addClientName, IM_ARRAYSIZE(addClientName));
            ImGui::InputText("Contact", addClientContact, IM_ARRAYSIZE(addClientContact));
            const char* ctypes[] = { "Buyer", "Seller", "Renter" };
            ImGui::Combo("Type", &addClientType, ctypes, IM_ARRAYSIZE(ctypes));

            if (!addClientError.empty()) ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", addClientError.c_str());

            ImGui::Separator();
            if (ImGui::Button("Confirm", ImVec2(120, 0))) {
                if (agency.addClientGUI(addClientID, addClientName, addClientContact, static_cast<ClientType>(addClientType), addClientError)) {
                    showAddClientModal = false;
                    addClientID = 0;
                    addClientName[0] = '\0'; addClientContact[0] = '\0'; addClientError = "";
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) showAddClientModal = false;
            ImGui::EndPopup();
        }

        // --- Edit Client Modal ---
        if (showEditClientModal) ImGui::OpenPopup("Edit Client ##Modal");
        if (ImGui::BeginPopupModal("Edit Client ##Modal", &showEditClientModal, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Editing Client ID: %d", editClientID);
            ImGui::InputText("Name", editClientName, IM_ARRAYSIZE(editClientName));
            ImGui::InputText("Contact", editClientContact, IM_ARRAYSIZE(editClientContact));
            const char* cTypes[] = { "Buyer", "Seller", "Renter" };
            ImGui::Combo("Role", &editClientType, cTypes, IM_ARRAYSIZE(cTypes));

            if (!editClientError.empty()) ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "%s", editClientError.c_str());

            ImGui::Separator();
            if (ImGui::Button("Confirm", ImVec2(120, 0))) {
                if (agency.editClientGUI(editClientID, editClientName, editClientContact, static_cast<ClientType>(editClientType), editClientError)) {
                    showEditClientModal = false;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) showEditClientModal = false;
            ImGui::EndPopup();
        }

        // --- Add Agent Modal ---
        if (showAddAgentModal) ImGui::OpenPopup("Add Agent ##Modal");
        if (ImGui::BeginPopupModal("Add Agent ##Modal", &showAddAgentModal, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::InputText("Name", addAgentName, IM_ARRAYSIZE(addAgentName));
            ImGui::InputText("Contact", addAgentContact, IM_ARRAYSIZE(addAgentContact));
            ImGui::InputDouble("Comm. %", &addAgentComm);

            if (!addAgentError.empty()) ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", addAgentError.c_str());

            ImGui::Separator();
            if (ImGui::Button("Confirm", ImVec2(120, 0))) {
                if (agency.addAgentGUI(addAgentID, addAgentName, addAgentContact, addAgentComm, addAgentError)) {
                    showAddAgentModal = false;
                    addAgentID = 0;
                    addAgentName[0] = '\0'; addAgentContact[0] = '\0'; addAgentError = "";
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) showAddAgentModal = false;
            ImGui::EndPopup();
        }

        // --- Edit Agent Modal ---
        if (showEditAgentModal) ImGui::OpenPopup("Edit Agent ##Modal");
        if (ImGui::BeginPopupModal("Edit Agent ##Modal", &showEditAgentModal, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Editing Agent ID: %d", editAgentID);
            ImGui::InputText("Name", editAgentName, IM_ARRAYSIZE(editAgentName));
            ImGui::InputText("Contact", editAgentContact, IM_ARRAYSIZE(editAgentContact));
            ImGui::InputDouble("Comm. %", &editAgentComm);

            if (!editAgentError.empty()) ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "%s", editAgentError.c_str());

            ImGui::Separator();
            if (ImGui::Button("Confirm", ImVec2(120, 0))) {
                if (agency.editAgentGUI(editAgentID, editAgentName, editAgentContact, editAgentComm, editAgentError)) {
                    showEditAgentModal = false;
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) showEditAgentModal = false;
            ImGui::EndPopup();
        }

        // --- Add Transaction Modal ---
        if (showAddTransModal) ImGui::OpenPopup("Record Transaction ##Modal");
        if (ImGui::BeginPopupModal("Record Transaction ##Modal", &showAddTransModal, ImGuiWindowFlags_AlwaysAutoResize)) {
            const char* transTypes[] = { "Sale", "Rental" };
            ImGui::Combo("Type", &addTransType, transTypes, IM_ARRAYSIZE(transTypes));
            ImGui::InputInt("Property ID", &addTransPropID);
            ImGui::InputInt("Client ID", &addTransClientID);
            ImGui::InputInt("Agent ID (0 if none)", &addTransAgentID);
            ImGui::InputDouble("Amount ($)", &addTransAmount);
            if (addTransType == 1) {
                ImGui::InputInt("Duration (Months)", &addTransDuration);
            }

            if (!addTransError.empty()) ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "%s", addTransError.c_str());

            ImGui::Separator();
            if (ImGui::Button("Confirm", ImVec2(120, 0))) {
                bool success = false;
                if (addTransType == 0) {
                    success = agency.recordSaleGUI(addTransID, addContractID, addTransPropID, addTransClientID, addTransAgentID, addTransAmount, addTransError);
                } else {
                    success = agency.recordRentalGUI(addTransID, addContractID, addTransPropID, addTransClientID, addTransAgentID, addTransAmount, addTransDuration, addTransError);
                }
                
                if (success) {
                    showAddTransModal = false;
                    addTransID = 0; addContractID = 0;
                    addTransPropID = 0; addTransClientID = 0; addTransAgentID = 0; addTransAmount = 0; addTransDuration = 12;
                    addTransError = "";
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) showAddTransModal = false;
            ImGui::EndPopup();
        }

        // --- Add User Modal ---
        if (showAddUserModal) ImGui::OpenPopup("Add User ##Modal");
        if (ImGui::BeginPopupModal("Add User ##Modal", &showAddUserModal, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::InputText("Username", addUserName, IM_ARRAYSIZE(addUserName));
            ImGui::InputText("Password", addUserPass, IM_ARRAYSIZE(addUserPass), ImGuiInputTextFlags_Password);
            const char* uRoles[] = { "Admin", "Agent", "Client" };
            ImGui::Combo("Role", &addUserRole, uRoles, IM_ARRAYSIZE(uRoles));

            if (!addUserError.empty()) ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "%s", addUserError.c_str());

            ImGui::Separator();
            if (ImGui::Button("Confirm", ImVec2(120, 0))) {
                string uname(addUserName);
                if (uname.empty()) {
                    addUserError = "Username cannot be empty.";
                } else if (agency.users.find(uname) != agency.users.end()) {
                    addUserError = "Username already exists.";
                } else {
                    UserRole r = UserRole::CLIENT;
                    if (addUserRole == 0) r = UserRole::ADMIN;
                    else if (addUserRole == 1) r = UserRole::AGENT;
                    agency.users[uname] = User(uname, addUserPass, r);
                    agency.saveUsers();
                    showAddUserModal = false;
                    addUserName[0] = '\0'; addUserPass[0] = '\0';
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) showAddUserModal = false;
            ImGui::EndPopup();
        }

        // --- Change Password Modal ---
        if (showChangePassModal) ImGui::OpenPopup("Change Password ##Modal");
        if (ImGui::BeginPopupModal("Change Password ##Modal", &showChangePassModal, ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Changing password for user: %s", changePassUsername.c_str());
            ImGui::InputText("New Password", changePassNew, IM_ARRAYSIZE(changePassNew), ImGuiInputTextFlags_Password);

            if (!changePassError.empty()) ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "%s", changePassError.c_str());

            ImGui::Separator();
            if (ImGui::Button("Confirm", ImVec2(120, 0))) {
                string newPwd(changePassNew);
                if (newPwd.empty()) {
                    changePassError = "Password cannot be empty.";
                } else {
                    auto it = agency.users.find(changePassUsername);
                    if (it != agency.users.end()) {
                        it->second.setPassword(newPwd);
                        agency.saveUsers();
                        showChangePassModal = false;
                    } else {
                        changePassError = "User not found.";
                    }
                }
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) showChangePassModal = false;
            ImGui::EndPopup();
        }

        // --- View Contract Modal ---
        if (showViewContractModal) ImGui::OpenPopup("View Contract Details ##Modal");
        if (ImGui::BeginPopupModal("View Contract Details ##Modal", &showViewContractModal, ImGuiWindowFlags_AlwaysAutoResize)) {
            auto it = agency.contractMap.find(viewContractID);
            if (it != agency.contractMap.end()) {
                auto& c = it->second;
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), "CONTRACT #%d", c->getID());
                ImGui::Separator();
                ImGui::Text("Type: %s", c->getContractType().c_str());
                ImGui::Text("Date: %s", c->getDate().c_str());
                ImGui::Text("Amount: $%.2f", c->getAmount());
                if (c->getDurationMonths() > 0) ImGui::Text("Duration: %d months", c->getDurationMonths());
                
                ImGui::Spacing();
                ImGui::TextColored(ImVec4(0.5f, 0.8f, 1.0f, 1.0f), "Property Details (ID:%d)", c->getPropertyID());
                auto pIt = agency.propertyMap.find(c->getPropertyID());
                if (pIt != agency.propertyMap.end()) {
                    ImGui::BulletText("Address: %s, %s", pIt->second->getAddress().c_str(), pIt->second->getCity().c_str());
                    ImGui::BulletText("Type: %s", pIt->second->getPropertyTypeStr().c_str());
                }

                ImGui::Spacing();
                ImGui::TextColored(ImVec4(0.5f, 0.8f, 1.0f, 1.0f), "Client Details (ID:%d)", c->getClientID());
                auto clIt = agency.clientMap.find(c->getClientID());
                if (clIt != agency.clientMap.end()) {
                    ImGui::BulletText("Name: %s", clIt->second->getName().c_str());
                    ImGui::BulletText("Contact: %s", clIt->second->getContactInfo().c_str());
                }
            } else {
                ImGui::Text("Contract not found.");
            }
            ImGui::Separator();
            if (ImGui::Button("Close", ImVec2(120, 0))) showViewContractModal = false;
            ImGui::EndPopup();
        }

        // --- View Transaction Modal ---
        if (showViewTransModal) ImGui::OpenPopup("Transaction Details ##Modal");
        if (ImGui::BeginPopupModal("Transaction Details ##Modal", &showViewTransModal, ImGuiWindowFlags_AlwaysAutoResize)) {
            auto it = agency.transactionMap.find(viewTransID);
            if (it != agency.transactionMap.end()) {
                auto& t = it->second;
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.8f, 1.0f), "TRANSACTION DETAILS");
                ImGui::Separator();
                ImGui::Text("Type: %s", (t->getType() == TransactionType::SALE ? "Sale" : "Rental"));
                ImGui::Text("Date: %s", t->getDate().c_str());
                ImGui::Text("Amount: $%.2f", t->getAmount());
                ImGui::Text("Commission: $%.2f", t->getCommission());
                
                ImGui::Spacing();
                ImGui::Text("Participants:");
                auto clIt = agency.clientMap.find(t->getClientID());
                ImGui::BulletText("Client: %s", clIt != agency.clientMap.end() ? clIt->second->getName().c_str() : "Unknown");
                
                auto oIt = agency.clientMap.find(t->getOwnerID());
                ImGui::BulletText("Owner/Landlord: %s", oIt != agency.clientMap.end() ? oIt->second->getName().c_str() : "Unknown");

                if (t->getAgentID() != 0) {
                    auto aIt = agency.agentMap.find(t->getAgentID());
                    ImGui::BulletText("Agent: %s", aIt != agency.agentMap.end() ? aIt->second->getName().c_str() : "Unknown");
                }
            } else {
                ImGui::Text("Transaction not found.");
            }
            ImGui::Separator();
            if (ImGui::Button("Close", ImVec2(120, 0))) showViewTransModal = false;
            ImGui::EndPopup();
        }
    }
};
